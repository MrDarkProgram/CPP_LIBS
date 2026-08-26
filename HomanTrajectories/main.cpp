#include "main.h"

// + #1   починить подсвечивающийся текст
// + #1.1 починить вылет проги когда отменяется выбор
// + #2   добавить кольца планетам гигантам (а ещё можно добавить пояс астероидов)
// + #3   добавить шкалу ускорений (чтоб можно было выбирать на сколько быстро ускорять)
//   #4   написать 100500 геттеров и сеттеров в плэнетдата (возможно)
//   #5   написать плашечку "сделал Коростов Иван, ссылка на гитхаб и т.п., Тихорецк 2026"
//   #6   убрать предупреждение с проверками ссылок на 0 (сделать всё по человечески) 
// + #7   починить вылет проги при попытке создать 2й маневр
//   #8   убрать костыль из spaceraft
// + #9   убрать возможность отматывать время назад во время физической симуляции
//   #10  добавить галочку включения и выключения учитывания массы 2го тела
// + #11  добавить название окна
//   #12  убрать консоль при открыти программы
//   #13  добавить поле для ввода названия файла звездной системы
// + #14  убрать из файла системы модификатор времени
// + #15  убрать возможность выбрать солнце
//   #16  добавить файл настроек
//   #17  добавить проверки на неправельно загруженный файл системы и файла настроек
//   #18  utils.hpp 128 навести порядок
//   #19  в целом везде навести порядок

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
float globalTimeModifier = 1;
float globalTimeModifierIndicator;
float globalTimeModifierIndicatorNeed;
constexpr int GTMI_substep = 50;

void SmoothTimer() {
	if (globalTimeModifierIndicator != globalTimeModifierIndicatorNeed) {
		if (globalTimeModifierIndicator < globalTimeModifierIndicatorNeed) globalTimeModifierIndicator += 1;
		if (globalTimeModifierIndicator > globalTimeModifierIndicatorNeed) globalTimeModifierIndicator -= 1;
		if (globalTimeModifierIndicator != globalTimeModifierIndicatorNeed && globalTimeModifierIndicator < globalTimeModifierIndicatorNeed) globalTimeModifier = pow(4, globalTimeModifierIndicatorNeed / GTMI_substep - 1) + pow(4, globalTimeModifierIndicatorNeed / GTMI_substep - 1) * 3 * (globalTimeModifierIndicator - int(globalTimeModifierIndicator / GTMI_substep) * GTMI_substep) / GTMI_substep;
		else if (globalTimeModifierIndicator != globalTimeModifierIndicatorNeed && globalTimeModifierIndicator > globalTimeModifierIndicatorNeed) globalTimeModifier = pow(4, globalTimeModifierIndicatorNeed / GTMI_substep) + pow(4, globalTimeModifierIndicatorNeed / GTMI_substep) * 3 * (globalTimeModifierIndicator - int(globalTimeModifierIndicator / GTMI_substep) * GTMI_substep) / GTMI_substep;
		else globalTimeModifier = pow(4, globalTimeModifierIndicatorNeed / GTMI_substep);
	}
}
void realTimeUpdate(float t) {
	start_time -= (globalTimeModifier - 1) * t;
}
long lastTime;
long getRealTime() {
	long time = clock() - start_time - stop_time;
	if (HohmannOrbit != 0 && time > HohmannOrbit->maneuver1Time && lastTime < HohmannOrbit->maneuver1Time) {
		lastTime = time;
		return HohmannOrbit->maneuver1Time;
	}
	lastTime = time;
	return time;
}

PlanetData* getPlanetDataByID(unsigned id) {
	for (int i = 0; i < planets.size(); i++) {
		if (planets[i].planet->id == id) return &planets[i];
	}
	return 0;
}

void m(int button, int action) {
	if (action == 1 && button == 0) {
		if (UniversalRender2::getSuperSelectedID() == 0) {
			UniversalRender2::setSuperSelectedID(UniversalRender2::getHighlightID());
		}
		else {
			if (UniversalRender2::getHighlightID() != 0 && UniversalRender2::getHighlightID() != UniversalRender2::getSuperSelectedID()) {
				delete HohmannOrbit;
				HohmannOrbit = new Spacecraft(planets, planets[0],
					*getPlanetDataByID(UniversalRender2::getSuperSelectedID()),
					*getPlanetDataByID(UniversalRender2::getHighlightID()),
					getRealTime());
				UniversalRender2::setRewrite();
				UniversalRender2::setSuperSelectedID(0);
			}
			else if (UniversalRender2::getHighlightID() == 0) {
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
		if (HohmannOrbit == 0 || HohmannOrbit != 0 && !(getRealTime() > HohmannOrbit->maneuver1Time && getRealTime() < HohmannOrbit->maneuver2Time)) {
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
		else {
			if (key == KEY_C && action == 1) {
				timeModeLabel->setTexturePosAndSize({ 64, 0 }, { 16, 16 });
			}
			else if (key == KEY_Z && action == 1) {
				timeModeLabel->setTexturePosAndSize({ 80, 0 }, { -16, 16 });
			}
			if ((key == KEY_C || key == KEY_Z) && action == 0) {
				timeModeLabel->setTexturePosAndSize({ 48, 0 }, { 16, 16 });
			}
		}
	}
	else if(!stop_time_bool && key == KEY_C && action == 1 ) {
		globalTimeModifierIndicatorNeed+= GTMI_substep;
	}
	else if (!stop_time_bool && key == KEY_Z && action == 1 && globalTimeModifierIndicatorNeed >= 0) {
		globalTimeModifierIndicatorNeed-= GTMI_substep;
	}
}

unsigned last_id = -1;
void u(float t) {
	SmoothTimer();
	if (stop_time_bool) {
		stop_time = clock() - stop_time_start;
		if (HohmannOrbit == 0 ||  HohmannOrbit != 0 && !(getRealTime() > HohmannOrbit->maneuver1Time && getRealTime() < HohmannOrbit->maneuver2Time)) {
			if (CameraMoveFixedUp::isKeyPressed(KEY_C)) stop_time_start += 10 * t;
			if (CameraMoveFixedUp::isKeyPressed(KEY_Z)) stop_time_start -= 10 * t;
		}
	}
	else realTimeUpdate(t);
	for(PlanetData& d : planets) moveObject(d, getRealTime());

	// =================

	if (HohmannOrbit != 0) {
		HohmannOrbit->update(getRealTime(), t, globalTimeModifier * !stop_time_bool);
		maneuverLabel->setText(std::string() +
			"T до маневра 1: " + std::to_string(long(HohmannOrbit->maneuver1Time - getRealTime()) / 1000) + " дней\n" +
			"T до маневра 2: " + std::to_string(long(HohmannOrbit->maneuver2Time - getRealTime()) / 1000) + " дней");
	}

	// =================

	unsigned id = UniversalRender2::getSelectedID();
	for (int i = 1; i < planets.size(); i++) {
		if (planets[i].planet->id == id) {
			UniversalRender2::setHighlightID(id);
			goto a;
		}
	}
	UniversalRender2::setHighlightID(0);
a:;

	id = UniversalRender2::getSuperSelectedID();
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

	timeLabel->setText(std::string() + "T: " + std::to_string(getRealTime() / 1000) + " дней\n1 cек. = " + std::to_string((long)globalTimeModifier) + " дней");
}

void init() {
	Window::create(1600, 900, "HohmannTrajectories");
	Window::setSkyColor({ 0, 0, 0, 1 });
	Window::addUpdateEvent(u);
	Window::setVSync(1);
	UniversalRender2::create();
	//UniversalRender2::highlightSelected();
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
	timeLabel = new GUIText({ 10, 70 }, 20, &t1, "", true);
	// информация об манёвре
	maneuverLabel = new GUIText({ 10, 70 + 22.5 * 2 }, 20, &t1, "", true);
	// информация об выбранном объекте
	infoLabel = new GUIText({ 10, 70 + 22.5 * 4 }, 20, &t1, "", true);

	// рисуем планеты
	generateObjects("solar_system.json", planets);
	for (PlanetData& d : planets) createObject(d);

	Spacecraft::InitModels();
	Physcraft::InitModels();

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