#pragma once
#include "main.h"

void init() {
	Window::create();
	UniversalRender::create();
	ConsoleFPS::create();
}

// сделать отсеивание граней         (в процессе)
//  - в какой библиотеке?
//  - пока в main_project, потом придумаем куда запихать
// ...
// перевести шейдеры на индексы
// сделать норм фпс
// добавить ubo и ssb встроенный генератор буфера принимающий размер в байтах и тип памяти
// добавить загрузку текстур
// сделать отдельную библиотеку мира (контролирует генерацию планет, ландшафта на них и т.п.)
// ...
// начать работать над... чем? (я чтото хотел тут написать, но забыл)
// сделать перевод в систему где z вертикаль (или нет)_
// 
Camera camera{};
void _update(float time) {
	//std::cout << "testRay: " << testRay(camera.getPos(), camera.getPos() + camera.getForward() * 100) << '\n';
}

void basis() {
	static object basis{};
	basis.mode = lines;
	basis.pos = { 0, 0, 0 };
	basis.vert = {
		{{0, 0, 0}, {}, {1, 0, 0, 1}}, {{1, 0, 0}, {}, {1, 0, 0, 1}},
		{{0, 0, 0}, {}, {0, 1, 0, 1}}, {{0, 1, 0}, {}, {0, 1, 0, 1}},
		{{0, 0, 0}, {}, {0, 0, 1, 1}}, {{0, 0, 1}, {}, {0, 0, 1, 1}},
	};
	UniversalRender::addObject(basis);
}

float minV{ 99 }, maxV{ 0 }, minL{ 99 }, maxL{ 0 };
void scene() {

	Window::addUpdateEvent(_update);

	/*tetrahedrons ts = generateIcosahedron();
	ts = { ts[0] };
	ts = subdivideTetrahedronsToSphere(ts, 0);
	ts = subdivideTetrahedrons(ts, 0);*/

	/*for (tetrahedron t : ts) {
		float v = abs(triple(t.a - t.d, t.b - t.d, t.c - t.d));
		minV = min(minV, v);
		maxV = max(maxV, v);
		minL = min(minL, min(min((t.a - t.d).length(), (t.b - t.d).length()), (t.c - t.d).length()));
		maxL = max(maxL, max(max((t.a - t.d).length(), (t.b - t.d).length()), (t.c - t.d).length()));
	}*/

	static Planet planet{};
	planet.Create(1);
	UniversalRender::addObject(planet.obj);


	//initPhys(); // инициализируем физику

	/*static object obj{};
	obj.scl = { 3, 3, 3 };
	obj.pos = { 0, 0, 8 };
	obj.addTetrahedron(ts, {1, 1, 1, 1}, triangles);
	UniversalRender::addObject(obj);
	createBody(obj);*/

	basis();
}

void world() {
	camera.setPos({ 0, 0, 0 });
	UniversalRender::setCameraPtr(&camera);

	CameraMoveFixedUp::create(&camera);

	Window::run();

	UniversalRender::free();
}

int graph_tests_main(void) {

	/*for (int i = 0; i < 5; i++) {
		tetrahedron t = { {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
		tetrahedrons ts = subdivideTetrahedrons({ t }, i);
		std::cout << ts.size() << ' ';
		std::vector<vec3> vs;
		for (tetrahedron& ti : ts) {
			bool na{}, nb{}, nc{}, nd{};
			for (vec3& v : vs) {
				if (ti.a == v) na = 1;
				if (ti.b == v) nb = 1;
				if (ti.c == v) nc = 1;
				if (ti.d == v) nd = 1;
			}
			if (!na) vs.push_back(ti.a);
			if (!nb) vs.push_back(ti.b);
			if (!nc) vs.push_back(ti.c);
			if (!nd) vs.push_back(ti.d);
		}
		int n = i + 1;
		std::cout << vs.size() << ' ' << n * (n + 2) * (n + 1) / 6 << '\n';
	}

	return 0;*/
	init();

	scene();

	world();
	return 0;
}