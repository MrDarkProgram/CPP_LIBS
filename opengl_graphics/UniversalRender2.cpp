#include "main.h"

std::vector<object> UniversalRender2::objects;
Shader* UniversalRender2::shader;
VertexBuffer* UniversalRender2::vbo;
VertexArray* UniversalRender2::vao;
VertexBuffer* UniversalRender2::vbo_dyn;
VertexArray* UniversalRender2::vao_dyn;
UniformBuffer* UniversalRender2::ubo;
ShaderBuffer* UniversalRender2::sbo;
bool UniversalRender2::rewrite{ 1 };
int UniversalRender2::count;
int UniversalRender2::point1;
int UniversalRender2::point2;
int UniversalRender2::point3;
unsigned UniversalRender2::selected_id;
unsigned UniversalRender2::highlight_id;
unsigned UniversalRender2::super_selected_id;
bool UniversalRender2::highlight_selected;
Camera* UniversalRender2::camera;

void UniversalRender2::create() {
	shader = new Shader("universal_shader.vert", "universal_shader.frag");
	int config[]{ 3, 3, 4, 2, 1, 1 };
	vbo = new VertexBuffer();
	vao = new VertexArray(config, 6);
	vbo_dyn = new VertexBuffer();
	vao_dyn = new VertexArray(config, 6);
	ubo = new UniformBuffer(0);
	glBufferData(GL_UNIFORM_BUFFER, 96, 0, GL_STREAM_DRAW);
	sbo = new ShaderBuffer(0);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 8, 0, GL_STREAM_READ);
	Window::addUpdateEvent(update);
	Window::addResizeEvent(resize);

	resize(Window::getWidth(), Window::getHeight());
}

void UniversalRender2::free() {
	delete shader;
	delete vbo;
	delete vao;
	delete vbo_dyn;
	delete vao_dyn;
	delete ubo;
}

object* UniversalRender2::addObject(object object) {
	return &objects.emplace_back(object);
}

bool UniversalRender2::removeObject(object* object) {
	for (int i = 0; i < objects.size(); i++) {
		if (&object[i] == object) {
			objects.erase(objects.begin() + i);
			return true;
		}
	}
	return false;
}

std::vector<float> UniversalRender2::collectObjectsToData(drawMode mode, bool alpha) {
	std::vector<float> data;
	for (object& object : objects) {
		if ((object.mode & 63) == mode && object.enable && object.alpha == alpha) {
			mat4 rotate = createRotation(object.rot);
			mat4 tr = createTranslate(object.pos);
			mat4 sc = createScale(object.scl);

			for (vertex vertex : object.vert) {
				vec3 pos = vertex.pos - object.center;
				pos = sc * pos;
				pos = rotate * pos;
				pos = tr * (pos /*- camera->getPos()*/);
				vec3 norm = vertex.norm;
				vec4 color{};
				if (object.color == color) color = vertex.color;
				else color = object.color;
				if (super_selected_id == object.id) {
					color.x = 1;
					color.y = 1;
					color.z /= 2;
				}
				else if ((highlight_selected && selected_id == object.id) || highlight_id == object.id) {
					color.x /= 2;
					color.y = 1;
					color.z /= 2;
				}
				norm = rotate * norm;
				if ((vertex.data & 128) == 128) pos = { pos.x / Window::getWidth() * 2 - 1, pos.y / Window::getHeight() * 2 - 1, pos.z };
				if ((object.mode & PosMode::leftUp) == PosMode::leftUp) pos.y += 2;
				if ((object.mode & PosMode::rightDown) == PosMode::rightDown) pos.x += 2;
				float _data[]{ pos.x, pos.y, pos.z, norm.x, norm.y, norm.z, color.x, color.y, color.z, color.w, vertex.tex.x, vertex.tex.y, *(float*)&vertex.data, *(float*)&object.id };
				data.insert(data.end(), _data, _data + 14);
			}
		}
	}
	return data;
}

void UniversalRender2::update(float time) {
	// ============================================== для статических объектов
	if (rewrite) {
		std::vector<float> data = collectObjectsToData(points, false);
		point1 = data.size();
		std::vector<float> data_tmp = collectObjectsToData(lines, false);
		data.insert(data.end(), data_tmp.begin(), data_tmp.end());
		point2 = data.size();
		data_tmp = collectObjectsToData(triangles, false);
		data.insert(data.end(), data_tmp.begin(), data_tmp.end());
		point3 = data.size();
		data_tmp = collectObjectsToData(triangles, true);
		data.insert(data.end(), data_tmp.begin(), data_tmp.end());

		vbo->use();
		glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_DYNAMIC_DRAW);
		count = data.size();
		rewrite = false;
	}

	// ============================================== для динамических объектов
	std::vector<float> data = collectObjectsToData(dyn_points, false);
	int point1dyn = data.size();
	std::vector<float> data_tmp = collectObjectsToData(dyn_lines, false);
	data.insert(data.end(), data_tmp.begin(), data_tmp.end());
	int point2dyn = data.size();
	data_tmp = collectObjectsToData(dyn_triangles, false);
	data.insert(data.end(), data_tmp.begin(), data_tmp.end());
	int point3dyn = data.size();
	data_tmp = collectObjectsToData(dyn_triangles, true);
	data.insert(data.end(), data_tmp.begin(), data_tmp.end());

	vbo_dyn->use();
	glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_STREAM_DRAW);

	// ============================================== камера
	ubo->use();
	if (camera) {
		double x, y;
		glfwGetCursorPos(Window::getWindow(), &x, &y);
		//std::cout << x << " " << y << std::endl;
		struct tmp {
			mat4 view;
			vec3 pos;
			float empty;
			vec2 cursorPos;
			vec2 windowPos;
		} data{ camera->getView(), camera->getPos(), 0, {float(x), Window::getHeight() - float(y)}, {(float)Window::getWidth(), (float)Window::getHeight()}};
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 96, &data);
	}
	else {

		float data[24]{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		};
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 96, &data);
	}

	// ============================================== буфер
	struct tmp {
		float depth;
		unsigned id;
	} data_{};
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, 8, &data_);
	selected_id = data_.id;
	data_.depth = 1;
	data_.id = 0;
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, 8, &data_);
	
	// ============================================== рендер
	shader->use();

	vao->use();
	glDrawArrays(GL_POINTS, 0, point1 / 14);
	glDrawArrays(GL_LINES, point1 / 14, (point2 - point1) / 14);
	glDrawArrays(GL_TRIANGLES, point2 / 14, (point3 - point2) / 14);

	vao_dyn->use();
	glDrawArrays(GL_POINTS, 0, point1dyn / 14);
	glDrawArrays(GL_LINES, point1dyn / 14, (point2dyn - point1dyn) / 14);
	glDrawArrays(GL_TRIANGLES, point2dyn / 14, (point3dyn - point2dyn) / 14);
	glDrawArrays(GL_TRIANGLES, point3dyn / 14, (data.size() - point3dyn) / 14);

	vao->use();
	glDrawArrays(GL_TRIANGLES, point3 / 14, (count - point3) / 14);


}

void UniversalRender2::resize(float w, float h) {
	struct tmp {
		float w;
		float h;
	} data{ w, h };
	//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 8, 8, &data);
	setRewrite();
}

void UniversalRender2::setRewrite() {
	rewrite = true;
}

void UniversalRender2::setCameraPtr(Camera* camera) {
	UniversalRender2::camera = camera;
}

void UniversalRender2::reserveObjects(unsigned n)
{
	objects.reserve(n);
}

unsigned UniversalRender2::getSelectedID()
{
	return selected_id;
}

unsigned UniversalRender2::getHighlightID()
{
	return highlight_id;
}

unsigned UniversalRender2::getSuperSelectedID()
{
	return super_selected_id;
}

void UniversalRender2::setHighlightID(unsigned u)
{
	highlight_id = u;
}

void UniversalRender2::setSuperSelectedID(unsigned u)
{
	super_selected_id = u;
}

void UniversalRender2::highlightSelected(bool b)
{
	highlight_selected = b;
}

object* UniversalRender2::getSelectedObject()
{
	for (object o : objects) {
		if (o.id == selected_id) return &o;
	}
	return 0;
}

object* UniversalRender2::getSuperSelectedObject()
{
	for (object o : objects) {
		if (o.id == super_selected_id) return &o;
	}
	return 0;
}
