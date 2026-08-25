#include "main.h"


DotCloud cloud{};
Camera camera{};
object cloud_obj;
vec3 s = vec3{ -1, -1, -1 }, p = vec3{ -1, -1, -1 };

void u(float t) {
	//vec3 s = cloud.checkRay(camera.getPos(), camera.getForward(), 64);
	s = vec3{ -1, -1, -1 };
	p = vec3{ -1, -1, -1 };
	cloud.checkRay(camera.getPos(), camera.getForward(), 64, s, p);
	cloud.setSelect(s);
	//std::cout << s.x << ' ' << s.y << ' ' << s.z << '\n';
	cloud_obj = cloud.generatePolygonModel();
}

void m(int b, int a) {
	if (a == 1) {
		if (b == 0) {
			if (s != vec3{ -1, -1, -1 }) {
				cloud.setDot(s, Matter::none);
			}
		}
		else if (b == 1) {
			if (p != vec3{ -1, -1, -1 }) {
				cloud.setDot(p, Matter::something);
			}
		}
	}
}

void init() {
	Window::create();
	//Window::disableBlockFaceCulling();
	Window::addUpdateEvent(u);
	UniversalRender::create();
	ConsoleFPS::create();
	CameraMoveFixedUp::addMouseEvent(m);
}

void scene() {


	// визуализация 3х базисных осей
	static object basis{};
	basis.mode = lines;
	basis.pos = { 0, 0, 0 };
	basis.vert = {
		{{0, 0, 0}, {}, {1, 0, 0, 1}}, {{1, 0, 0}, {}, {1, 0, 0, 1}},
		{{0, 0, 0}, {}, {0, 1, 0, 1}}, {{0, 1, 0}, {}, {0, 1, 0, 1}},
		{{0, 0, 0}, {}, {0, 0, 1, 1}}, {{0, 0, 1}, {}, {0, 0, 1, 1}},
	};
	UniversalRender::addObject(basis);

	//cloud_obj = cloud.generatePolygonModel();
	UniversalRender::addObject(cloud_obj);

	// добавление управляемой камеры
	camera.setPos({ 0, 0, -40 });
	UniversalRender::setCameraPtr(&camera);
	CameraMoveFixedUp::create(&camera);
}

void run() {
	Window::run();
	UniversalRender::free();
}

int main() {

	init();
	scene();
	run();

	return 0;
}