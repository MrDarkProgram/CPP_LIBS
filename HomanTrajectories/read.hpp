#include "main.h"

struct PlanetData
{
	// Название планеты
	std::string Name;

	// Орбитальные характеристики

	// Большая полуось (тыс. км)
	float SemiMajorAxis;
	// Эксцентриситет
	float Eccentricity;
	// Сидерический период обращения (дн)
	float SiderealOrbitalPeriod;
	// Средняя аномалия (град (в файле json))
	float MeanAnomaly;
	// Наклонение (град (в файле json))
	float Inclination;
	// Долгота восходящего узла (град (в файле json))
	float LongitudeOfTheAscendingNode;
	// Аргумент перицентра (гра (в файле json)д)
	float ArgumentOfPeriapsis;

	// Физические характеристики
	
	// Экваториальный радиус (тыс. км)
	float EquatorialRadius;
	// Полярный радиус (тыс. км)
	float PolarRadius;
	// Масса (кг * 10^23)
	float  Mass;
	// Сидерический период вращения (дн)
	float SiderealRotationPeriod;
	// Наклон оси (град (в файле json))
	float AxialTilt;

	// Другие характеристики

	// Модификатор размера планеты
	float RadiusModifier;
	// Красная составляющая цвета модели [0;1]
	float ColorR;
	// Зеленая составляющая цвета модели [0;1]
	float ColorG;
	// Синяя составляющая цвета модели [0;1]
	float ColorB;

	// Вспомогательные переменные
	
	// Кватернион наклона орбиты планеты
	quaternion q;
	// Матрица наклона орбиты планеты
	mat4 m;
	// Объект планеты
	object* planet;
	// Объект орбиты
	object* orbit;
	// Позиция объекта в прошлом кадре
	vec3 lastPos;

	void copyOrbitDataOnly(PlanetData& p) {
		SemiMajorAxis = p.SemiMajorAxis;
		Eccentricity = p.Eccentricity;
		SiderealOrbitalPeriod = p.SiderealOrbitalPeriod;
		MeanAnomaly = p.MeanAnomaly;
		Inclination = p.Inclination;
		LongitudeOfTheAscendingNode = p.LongitudeOfTheAscendingNode;
		ArgumentOfPeriapsis = p.ArgumentOfPeriapsis;
		calculateQM();
	}
	void calculateQM() {
		q = fromEulerAngles({ 0, LongitudeOfTheAscendingNode, 0 }) * fromEulerAngles({ 0, 0, Inclination }) * fromEulerAngles({ 0, ArgumentOfPeriapsis, 0 });
		m = createRotation(q);
	}
};

struct Planets : public std::vector<PlanetData> {
	float GlobalRadiusModifier;
	float GlobalSemiMajorAxisModifier;
	float GlobalTimeModifier;
};

void generateObjects(const char* path, Planets& objects) {
	std::fstream f(path);
	json data = json::parse(f);
	auto& planets = data["planets"];

	objects.GlobalRadiusModifier = data["GlobalRadiusModifier"];
	objects.GlobalSemiMajorAxisModifier = data["GlobalSemiMajorAxisModifier"];
	objects.GlobalTimeModifier = data["GlobalTimeModifier"];
	objects.reserve(planets.size());
	for (int i = 0; i < planets.size(); i++) {
		objects.push_back({});
		objects[i].RadiusModifier = planets[i]["RadiusModifier"];

		objects[i].Name = planets[i]["Name"];
		objects[i].SemiMajorAxis = planets[i]["SemiMajorAxis"] * objects.GlobalSemiMajorAxisModifier;
		objects[i].Eccentricity = planets[i]["Eccentricity"];
		objects[i].SiderealOrbitalPeriod = planets[i]["SiderealOrbitalPeriod"];
		objects[i].MeanAnomaly = planets[i]["MeanAnomaly"] * 3.1415 / 180;
		objects[i].Inclination = planets[i]["Inclination"] * 3.1415 / 180;
		objects[i].LongitudeOfTheAscendingNode = planets[i]["LongitudeOfTheAscendingNode"] * 3.1415 / 180;
		objects[i].ArgumentOfPeriapsis = planets[i]["ArgumentOfPeriapsis"] * 3.1415 / 180;
		objects[i].EquatorialRadius = planets[i]["EquatorialRadius"] * objects[i].RadiusModifier * objects.GlobalRadiusModifier;
		objects[i].PolarRadius = planets[i]["PolarRadius"] * objects[i].RadiusModifier * objects.GlobalRadiusModifier;
		objects[i].Mass = planets[i]["Mass"];
		objects[i].SiderealRotationPeriod = planets[i]["SiderealRotationPeriod"];
		objects[i].AxialTilt = planets[i]["AxialTilt"] * 3.1415 / 180;
		objects[i].ColorR = planets[i]["colorR"];
		objects[i].ColorG = planets[i]["colorG"];
		objects[i].ColorB = planets[i]["colorB"];
	}
}