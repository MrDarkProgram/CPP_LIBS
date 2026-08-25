#include "main.h"

// починить подсвечивающийся текст
// добавить кольца планетам гигантам (а ещё можно добавить пояс астероидов)
// добавить шкалу ускорений (чтоб можно было выбирать на сколько быстро ускорять)
// написать 100500 геттеров и сеттеров в плэнетдата (возможно)
// написать плашечку "сделал Коростов Иван, ссылка на гитхаб и т.п., Тихорецк 2026"
// убрать предупреждение с проверками ссылок на 0 (сделать всё по человечески) 
// починить вылет проги при попытке создать 2й маневр
// убрать костыль из spaceraft
// убрать возможность отматывать время назад во время физической симуляции
// добавить галочку включения и выключения учитывания массы 2го тела
// добавить название окна

Camera camera{};
Planets planets{};
bool stop_time_bool;
long start_time;
long stop_time_start;
long stop_time;
GUIElement* timeModeLabel;
GUIText* timeLabel;
GUIText* maneuverLabel;
GUIText* infoLabel;
Spacecraft* HohmannOrbit;
//Physcraft* physcraft;

long getRealTime() {
	return (clock() - start_time - stop_time) * planets.GlobalTimeModifier;
}

PlanetData* getPlanetDataByID(unsigned id) {
	for (int i = 0; i < planets.size(); i++) {
		if (planets[i].planet->id == id) return &planets[i];
	}
	return 0;
}

void m(int button, int action) {
	if (action == 1 && button == 0) {
		if(UniversalRender2::getSuperSelectedID() == 0) UniversalRender2::setSuperSelectedID(UniversalRender2::getSelectedID());
		else {
			if (UniversalRender2::getSelectedID() != 0 && UniversalRender2::getSelectedID() != UniversalRender2::getSuperSelectedID()) {
				/*calculateHomanOrbit(HohmannOrbit, planets, planets[0],
					*getPlanetDataByID(UniversalRender2::getSuperSelectedID()),
					*getPlanetDataByID(UniversalRender2::getSelectedID()), getRealTime());
				HohmannOrbit.orbit->vert = drawOrbit(HohmannOrbit);
				HohmannOrbit.planet->addTriangles(generateSphere(0), {HohmannOrbit.ColorR, HohmannOrbit.ColorG, HohmannOrbit.ColorB, 1}, dyn_triangles);*/
				delete HohmannOrbit;
				HohmannOrbit = new Spacecraft(planets, planets[0],
					*getPlanetDataByID(UniversalRender2::getSuperSelectedID()),
					*getPlanetDataByID(UniversalRender2::getSelectedID()),
					getRealTime());
				UniversalRender2::setRewrite();
				UniversalRender2::setSuperSelectedID(0);
			}
			else if (UniversalRender2::getSelectedID() == 0) {
				UniversalRender2::setSuperSelectedID(0);
			}
		}
	}
}

void k(int key, int scan_code, int action, int mode) {
	if (key == KEY_X && action == 1) {
		stop_time_bool = !stop_time_bool;
		if (stop_time_bool) {
			stop_time_start = clock() - stop_time;
			timeModeLabel->setTexturePosAndSize({ 48, 0 }, { 16, 16 });
		}
		else {
			timeModeLabel->setTexturePosAndSize({ 0, 0 }, { 16, 16 });
		}
	}
	if (stop_time_bool) {
		if (key == KEY_C && action == 1) {
			timeModeLabel->setTexturePosAndSize({ 32, 0 }, { 16, 16 });
		}
		else if (key == KEY_Z && action == 1) {
			timeModeLabel->setTexturePosAndSize({ 48, 0 }, { -16, 16 });
		}
		if ((key == KEY_C || key == KEY_Z) && action == 0) {
			timeModeLabel->setTexturePosAndSize({ 48, 0 }, { 16, 16 });
		}
	}
	else if(!stop_time_bool && key == KEY_C) {
		if (action == 1) {
			timeModeLabel->setTexturePosAndSize({ 16, 0 }, { 16, 16 });
		}
		else if (action == 0) {
			timeModeLabel->setTexturePosAndSize({ 0, 0 }, { 16, 16 });
		}
	}
}

unsigned last_id = -1;
void u(float t) {
	if (stop_time_bool) {
		stop_time = clock() - stop_time_start;
		if (CameraMoveFixedUp::isKeyPressed(KEY_C)) stop_time_start += 10 * t;
		if (CameraMoveFixedUp::isKeyPressed(KEY_Z)) stop_time_start -= 10 * t;
	}
	else {
		if (CameraMoveFixedUp::isKeyPressed(KEY_C)) start_time -= 19 * t;
	}
	for(PlanetData& d : planets) moveObject(d, getRealTime());

	// =================
	//moveObject(HohmannOrbit, getRealTime() - tNow);

	if (HohmannOrbit != 0) {
		HohmannOrbit->update(getRealTime(), t);
		maneuverLabel->setText(std::string() +
			"T до маневра 1: " + std::to_string(long(HohmannOrbit->maneuver1Time - getRealTime()) / 1000) + " дней\n" +
			"T до маневра 2: " + std::to_string(long(HohmannOrbit->maneuver2Time - getRealTime()) / 1000) + " дней");
	}

	// =================

	unsigned id = UniversalRender2::getSuperSelectedID();
	if (id == 0 && last_id != id) {
		last_id = id;
		infoLabel->setText("выберите планету...");
	}
	else 
		for (int i = 0; i < planets.size(); i++) {
			if (planets[i].planet->id == id && last_id != id) {
				last_id = id;
				infoLabel->setText(
					std::string() +
					"Имя: " + planets[i].Name + "\n" +
					//"V:  " + std::to_string(calculateVByTime(planets, planets[0], planets[i], getRealTime())) + "\n" +
					//"T:  " + std::to_string(calculateT(planets, planets[0], planets[i])) + "\n" +
					"");
			}
		}

	// =================

	timeLabel->setText(std::string() + "T: " + std::to_string(getRealTime() / 1000) + " дней");
}

void init() {
	Window::create();
	Window::setSkyColor({ 0, 0, 0, 1 });
	Window::addUpdateEvent(u);
	Window::setVSync(1);
	UniversalRender2::create();
	UniversalRender2::highlightSelected();
	//ConsoleFPS::create();
	setlocale(LC_ALL, "");
}

void scene() {
	UniversalRender2::reserveObjects(30);

	// визуализация 3х базисных осей
	object basis{};
	basis.mode = lines;
	basis.pos = { 0, 0, 0 };
	basis.vert = {
		{{0, 0, 0}, {}, {1, 0, 0, 1}, {}, 0}, {{1, 0, 0}, {}, {1, 0, 0, 1}, {}, 0},
		{{0, 0, 0}, {}, {0, 1, 0, 1}, {}, 0}, {{0, 1, 0}, {}, {0, 1, 0, 1}, {}, 0},
		{{0, 0, 0}, {}, {0, 0, 1, 1}, {}, 0}, {{0, 0, 1}, {}, {0, 0, 1, 1}, {}, 0},
	};
	UniversalRender2::addObject(basis);

	// GUI
	static Texture t0("textureMap.png", 0);
	static Texture t1("font.png", 1);
	// иконка течения времени
	timeModeLabel = new GUIElement({ 10, 10 }, { 50, 50 }, &t0, { 0, 0 }, {16, 16}, true);
	// информация о времени
	timeLabel = new GUIText({ 10, 70 }, 15, &t1, "", true);
	// информация об манёвре
	maneuverLabel = new GUIText({ 10, 90 }, 15, &t1, "", true);
	// информация об выбранном объекте
	infoLabel = new GUIText({ 10, 140 }, 15, &t1, "", true);

	// рисуем планеты
	generateObjects("solar_system.json", planets);
	for (PlanetData& d : planets) createObject(d);

	// добавление управляемой камеры
	camera.setPos({ 0, 100, 200 });
	camera.setForward({0, 0, -1});
	camera.setFarFront(100000);
	UniversalRender2::setCameraPtr(&camera);
	CameraMoveFixedUp::setYRotDeg(270);
	CameraMoveFixedUp::create(&camera, false, 0.1, 0.15, true, false);
	CameraMoveFixedUp::addKeyEvent(k);
	CameraMoveFixedUp::addMouseEvent(m);

	// =================

	//physcraft = new Physcraft(planets, planets[0], planets[0], planets[0]);
	//physcraft->setPositionAndVelocity({160, 0, 0}, {0, 0, -28.8});
	//physCraft->setPositionAndVelocity({190, 0, 0}, {0, 0, -26.43});
}

void runAndFree() {
	Window::run();
	UniversalRender2::free();
	//delete timeModeLabel;
}

int main() {

	init();
	scene();
	start_time = clock();
	runAndFree();
	return 0;
}