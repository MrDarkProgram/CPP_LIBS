#include "main.h"

void Shader::checkShaderError(int shader, int shaderType) {
	int success;
	char log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, log);
		const char* name = "";
		switch (shaderType)
		{
		case GL_VERTEX_SHADER:
			name = "VERT";
			break;
		case GL_GEOMETRY_SHADER:
			name = "GEOM";
			break;
		case GL_FRAGMENT_SHADER:
			name = "FRAG";
			break;
		default:
			name = "NAN";
			break;
		}
		std::cout << "ERROR::SHADER::" << name << "::COMPILATION_FAILED\n" << log << std::endl;
	}
}

void Shader::checkProgramError(int program) {
	int success;
	char log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, 0, log);
		std::cout << "ERROR::LINK::COMPILATION_FAILED\n" << log << std::endl;
	}
}

int Shader::createShader(const char* path, int shaderType) {
	std::ifstream file = checkFilePathAndOpen(path);
	std::string line{};
	std::string text{};
	while (std::getline(file, line)) text += checkIncludesAndInclude(line);
	file.close();

	int shader = glCreateShader(shaderType);
	const char* code = text.c_str();
	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	checkShaderError(shader, shaderType);

	glAttachShader(program, shader);
	glDeleteShader(shader);

	return shader;
}

std::string Shader::checkIncludesAndInclude(std::string& line) {
	if (line.size() > 0 && line.starts_with("#include")) {
		int start = -1, end = -1;
		for (int i = 0; i < line.size(); i++) {
			if (line.substr(i, 1) == "\"") {
				start = end;
				end = i;
			}
		}
		std::string path = line.substr(start + 1, end - start - 1);
		std::ifstream file = checkFilePathAndOpen(path.c_str());
		if (file) {
			std::string text{};
			while (std::getline(file, line)) text += checkIncludesAndInclude(line);
			file.close();
			return text;
		}
		return "";
	}
	return line + '\n';
}

std::ifstream Shader::checkFilePathAndOpen(const char* path) {
	std::ifstream file{ path };
	if (!file.is_open()) {
		file.open(std::string("../x64/Release/") + path);
		if (!file.is_open()) {
			std::cout << "ERROR: file " << path << " not found!" << std::endl;
		}
	}
	return file;
}

Shader::Shader(const char* path_vert, const char* path_frag) {
	program = glCreateProgram();

	int vert = createShader(path_vert, GL_VERTEX_SHADER);
	int frag = createShader(path_frag, GL_FRAGMENT_SHADER);

	glLinkProgram(program);

	checkProgramError(program);

	use();
}

Shader::Shader(const char* path_vert, const char* path_geom, const char* path_frag) {

	program = glCreateProgram();

	int vert = createShader(path_vert, GL_VERTEX_SHADER);
	int geom = createShader(path_geom, GL_GEOMETRY_SHADER);
	int frag = createShader(path_frag, GL_FRAGMENT_SHADER);

	glLinkProgram(program);

	checkProgramError(program);

	use();
}

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::use() const {
	glUseProgram(program);
}





VertexArray::VertexArray(int* config, int size) {
	glGenVertexArrays(1, &VAO);
	use();

	int sum = 0;
	for (int i = 0; i < size; i++) sum += config[i];

	int offset = 0;
	for (int i = 0; i < size; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, config[i], GL_FLOAT, false, sum * sizeof(float), (void*)(offset * sizeof(float)));
		offset += config[i];
	}
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::use() const {
	glBindVertexArray(VAO);
}






VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &VBO);
	use();
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &VBO);
}

void VertexBuffer::use() const {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}





UniformBuffer::UniformBuffer(int index) {
	glGenBuffers(1, &UBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, index, UBO);
	use();
}

UniformBuffer::~UniformBuffer() {
	glDeleteBuffers(1, &UBO);
}

void UniformBuffer::use() const {
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
}





ShaderBuffer::ShaderBuffer(int index) {
	glGenBuffers(1, &SSB);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, SSB);
	use();
}

ShaderBuffer::~ShaderBuffer() {
	glDeleteBuffers(1, &SSB);
}

void ShaderBuffer::use() const {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSB);
}





Texture::Texture(std::string path, unsigned position)
{
	this->position = position;
	glGenTextures(1, &texture);
	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if(image == 0) image = SOIL_load_image((std::string("../x64/Release/") + path).c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] image;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::SetPosition(unsigned position)
{
	this->position = position;
}

unsigned Texture::GetTextureWidth() const
{
	return width;
}

unsigned Texture::GetTextureHeight() const
{
	return height;
}

void Texture::use() const {
	glActiveTexture(GL_TEXTURE0 + position);
	glBindTexture(GL_TEXTURE_2D, texture);
}