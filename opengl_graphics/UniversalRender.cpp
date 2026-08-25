#include "main.h"

std::vector<object*> UniversalRender::objects;
Shader* UniversalRender::shader;
VertexBuffer* UniversalRender::vbo;
VertexArray* UniversalRender::vao;
VertexBuffer* UniversalRender::vbo_dyn;
VertexArray* UniversalRender::vao_dyn;
UniformBuffer* UniversalRender::ubo;
bool UniversalRender::rewrite{1};
int UniversalRender::count;
int UniversalRender::point1;
int UniversalRender::point2;
int UniversalRender::point3;
Camera* UniversalRender::camera;

void UniversalRender::create() {
	shader = new Shader("universal_shader.vert", "universal_shader.frag");
	int config[]{ 3, 3, 4, 2, 1, 1 };
	vbo = new VertexBuffer();
	vao = new VertexArray(config, 6);
	vbo_dyn = new VertexBuffer();
	vao_dyn = new VertexArray(config, 6);
	ubo = new UniformBuffer(0);
	glBufferData(GL_UNIFORM_BUFFER, 76, 0, GL_STREAM_DRAW);
	Window::addUpdateEvent(update);
	Window::addResizeEvent(resize);

	resize(Window::getWidth(), Window::getHeight());
}

void UniversalRender::free() {
	delete shader;
	delete vbo;
	delete vao;
	delete vbo_dyn;
	delete vao_dyn;
	delete ubo;
}

int UniversalRender::addObject(object& object) {
	objects.push_back(&object);
	return objects.size() - 1;
}

void UniversalRender::removeObject(int index) {
	objects.erase(objects.begin() + index);
}

std::vector<float> UniversalRender::collectObjectsToData(drawMode mode, bool alpha) {
	std::vector<float> data;
	for (object* object_ptr : objects) {
		object& object = *object_ptr;
		if (object.mode == mode && object.enable && object.alpha == alpha) {
			mat4 rotate = createRotation(object.rot);
			mat4 tr = createTranslate(object.pos);
			mat4 sc = createScale(object.scl);

			for (vertex vertex : object.vert) {
				vec3 pos = vertex.pos - object.center;
				pos = sc * pos;
				pos = rotate * pos;
				pos = tr * (pos /*- camera->getPos()*/);
				vec3 norm = vertex.norm;
				norm = rotate * norm;
				if ((vertex.data & 128) == 128) pos = {pos.x / Window::getWidth() * 2 - 1, pos.y / Window::getHeight() * 2 + 1, pos.z};
				if (object.color == vec4{}) {
					float _data[]{ pos.x, pos.y, pos.z, norm.x, norm.y, norm.z, vertex.color.x, vertex.color.y, vertex.color.z, vertex.color.w, vertex.tex.x, vertex.tex.y, *(float*)&vertex.data, *(float*)&object.id };
					data.insert(data.end(), _data, _data + 14);
				}
				else {
					float _data[]{ pos.x, pos.y, pos.z, norm.x, norm.y, norm.z, object.color.x, object.color.y, object.color.z, object.color.w, vertex.tex.x, vertex.tex.y, *(float*)&vertex.data, *(float*)&object.id };
					data.insert(data.end(), _data, _data + 14);
				}
			}
		}
	}
	return data;
}

void UniversalRender::update(float time) {
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
		struct tmp {
			mat4 view;
			vec3 pos;
		} data{ camera->getView(), camera->getPos() };
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 76, &data);
	}
	else {

		float data[19]{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
			0, 0, 0
		};
		glBufferSubData(GL_UNIFORM_BUFFER, 0, 76, &data);
	}

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

void UniversalRender::resize(float w, float h) {
	struct tmp {
		float w;
		float h;
	} data{w, h};
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 8, 8, &data);
}

void UniversalRender::setRewrite() {
	rewrite = true;
}

void UniversalRender::setCameraPtr(Camera* camera) {
	UniversalRender::camera = camera;
}