#include "main.h"

// *10^-11
constexpr float G = 6.674; 

float calculateE(float e, double M) {
	float E = M;
	for (int i = 0; i < 100; i++) {
		E = e * sin(E) + M;
	}
	return E;
}

float calculateM(float M0, double T, float t) {
	double M = M0 + 2 * 3.1415 * t / T;
a:	if (M > 6.2832) {
		M -= 6.2832;
		goto a;
	}
	return (float)M;
}

float calculateF(float e, float E) {
	float t = sqrt((1 + e) / (1 - e)) * tan(E / 2);
	return atan(t) * 2;
}

float calculateF(PlanetData& data, float global_t) {
	return calculateF(data.Eccentricity, calculateE(data.Eccentricity, calculateM(data.MeanAnomaly, data.SiderealOrbitalPeriod, global_t / 1000)));
}

float calculateT(Planets planets, PlanetData& star, PlanetData& orbit) {
	return 2 * 3.1415 * sqrt(pow((double)orbit.SemiMajorAxis / planets.GlobalSemiMajorAxisModifier, 3) / G / star.Mass * 0.00013393);
}

float calculateOffset(PlanetData& data, float global_t) {
	return 3.1415 - calculateE(data.Eccentricity, calculateM(data.MeanAnomaly, data.SiderealOrbitalPeriod, global_t / 1000));
}

float calculateOffsetF(PlanetData& data, float global_t) {
	return 3.1415 - calculateF(data.Eccentricity, calculateE(data.Eccentricity, calculateM(data.MeanAnomaly, data.SiderealOrbitalPeriod, global_t / 1000)));
}

float calculateOffsetAbsoluteF(PlanetData& data, float global_t) {
	return calculateOffsetF(data, global_t) - data.ArgumentOfPeriapsis - data.LongitudeOfTheAscendingNode;
}

float calculateOffsetFromAbsoluteF(PlanetData& data, float af) {
	float f = af + data.ArgumentOfPeriapsis + data.LongitudeOfTheAscendingNode;
	f -= 3.1415;
	f = sqrt((1 - data.Eccentricity) / (1 + data.Eccentricity)) * tan(f / 2);
	f = atan(f) * 2;
	f += 3.1415;
	return f;
}

float calculateMFromOffset(PlanetData& data, float offset) {
	float t = 3.1415 - offset;
	return t - data.Eccentricity * sin(t);
}

float calculateTtFromMAndM0(float M0, float M, float T) {
	return (M - M0) * T / 2 / 3.1415;
}

float calculateV(Planets& planets, PlanetData& star, PlanetData& data, float trueAnomaly) {
	float p = data.SemiMajorAxis / planets.GlobalSemiMajorAxisModifier * (1 - data.Eccentricity * data.Eccentricity);
	return sqrt(G * star.Mass / p * (1 + 2 * data.Eccentricity * cos(trueAnomaly) + data.Eccentricity * data.Eccentricity));
}

float calculateVByTime(Planets& planets, PlanetData& star, PlanetData& data, float realTime) {
	return calculateV(planets, star, data, calculateF(data, realTime));
}

float normalizeT(float t) {
a:	if (t > 3.1415) {
		t -= 6.2830;
		goto a;
	}
	else if (t < -3.1415) {
		t += 6.2830;
		goto a;
	}
	return t;
}

float normalizeTPlus(float t) {
a:	if (t < 0) {
		t += 6.2830;
		goto a;
	}
	return t;
}

void moveObject(PlanetData& data, double global_t) {
	vec3 pos = {};
	if (data.SiderealOrbitalPeriod != 0) {
		float a = data.SemiMajorAxis;
		float e = data.Eccentricity;
		float b = sqrt((1 - e * e) * a * a);
		float c = e * a;
		float offset = calculateOffset(data, global_t);
		pos = vec3{ a * cos(offset) + c, 0, b * sin(offset) };
	}
	data.lastPos = data.planet->pos;
	data.planet->pos = data.m * pos;
	quaternion r = fromEulerAngles({ data.AxialTilt, 0, 0 });
	if (data.SiderealRotationPeriod != 0) r = r * fromEulerAngles({ 0, (float)global_t / 1000 * 2 * 3.1415f / data.SiderealRotationPeriod, 0 });
	data.planet->rot = data.q * r;
	data.planet->rot.norm_this();
}

void createObject(PlanetData& data) {
	data.planet = UniversalRender2::addObject({});
	data.planet->scl = { data.EquatorialRadius * 2, data.PolarRadius * 2, data.EquatorialRadius * 2 };
	data.planet->addTriangles(generateSphere(2), { data.ColorR, data.ColorG, data.ColorB, 1 }, dyn_triangles);
	data.calculateQM();

	data.orbit = UniversalRender2::addObject({});
	data.orbit->mode = lines;
	data.orbit->vert = drawOrbit(data);
}

long tNow{};
long tManeuver{};
float A1;
float A2;
float AO; // удалить
double T;
void calculateHomanOrbit(PlanetData& data, Planets& planets, PlanetData& star, PlanetData& data1, PlanetData& data2, double global_t) {
	if (&data1 == 0 || &data2 == 0 || data1.SiderealOrbitalPeriod == 0 || data2.SiderealOrbitalPeriod == 0) return;
	float t{};
	T = 0;
	for (int i = 0; i < 200; i++) {
		float a = data1.SemiMajorAxis;
		float e = data1.Eccentricity;
		float b = sqrt((1 - e * e) * a * a);
		float c = e * a;
		float offset = calculateOffset(data1, global_t + T);
		vec3 pos = data1.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };
		float a1 = pos.length();

		a = data2.SemiMajorAxis;
		e = data2.Eccentricity;
		b = sqrt((1 - e * e) * a * a);
		c = e * a;
		offset = calculateOffsetFromAbsoluteF(data2, calculateOffsetAbsoluteF(data1, global_t + T) - 3.1415);
		pos = data2.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };

		float a2 = pos.length();

		a = (a1 + a2) / 2;
		c = std::max(a1, a2) - a;
		e = c / a;
		//b = sqrt((1 - e * e) * a * a);
		data.SemiMajorAxis = a;
		data.Eccentricity = e;
		data.LongitudeOfTheAscendingNode = data1.LongitudeOfTheAscendingNode;
		data.Inclination = data1.Inclination;
		//data.ArgumentOfPeriapsis = data1.ArgumentOfPeriapsis + calculateE(data1.Eccentricity, calculateM(data1.MeanAnomaly, data1.SiderealOrbitalPeriod, global_t / 1000)) + (a1 > a2 ? 3.1415 : 0);
		data.ArgumentOfPeriapsis = data1.ArgumentOfPeriapsis - calculateOffsetF(data1, global_t + T) + (a2 > a1 ? 3.1415 : 0);
		//data.ArgumentOfPeriapsis = data1.ArgumentOfPeriapsis - calculateOffsetF(data1, global_t + T) + 3.1415;
		data.calculateQM();
		tNow = global_t + T;
		data.SiderealOrbitalPeriod = calculateT(planets, star, data);
		A1 = normalizeT(calculateOffsetAbsoluteF(data1, global_t + T));
		A2 = normalizeT(calculateOffsetAbsoluteF(data2, global_t + T + calculateT(planets, star, data) * 500));
		data.MeanAnomaly = (a2 > a1 ? 3.1415 : 0);
		AO = normalizeT(calculateOffsetAbsoluteF(data, global_t + T - tNow));
		data.MeanAnomaly = (a2 < a1 ? 3.1415 : 0);
		t = normalizeTPlus(AO - A2);
		//if(a2 > a1) t = normalizeTPlus(AO - A2);
		//else t = normalizeTPlus(A2 - AO);
		if (t < 0.001) return;
		if (a2 > a1) T += std::min(data1.SiderealOrbitalPeriod, data2.SiderealOrbitalPeriod) * 1000 * t / 6.2830 / 2;
		else T += std::min(data1.SiderealOrbitalPeriod, data2.SiderealOrbitalPeriod) * 1000 * (1 - t / 6.2830) / 2;
		//std::cout << "итерация " << i << ":\n\tразность: " << t << " рад.\n\tвремя до маневра: " << int(T / 1000) << "\n";
	}
}

void calculateHomanOrbit2(PlanetData& data, Planets& planets, PlanetData& star, PlanetData& data1, PlanetData& data2, double global_t) {
	if (&data1 == 0 || &data2 == 0 || data1.SiderealOrbitalPeriod == 0 || data2.SiderealOrbitalPeriod == 0) return;

	float a = data1.SemiMajorAxis;
	float e = data1.Eccentricity;
	float b = sqrt((1 - e * e) * a * a);
	float c = e * a;
	float offset = calculateOffsetFromAbsoluteF(data1, calculateOffsetAbsoluteF(data2, global_t) - 3.1415);
	vec3 pos = data1.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };
	float a1 = pos.length();

	a = data2.SemiMajorAxis;
	e = data2.Eccentricity;
	b = sqrt((1 - e * e) * a * a);
	c = e * a;
	offset = calculateOffset(data2, global_t);
	pos = data2.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };
	float a2 = pos.length();

	a = (a1 + a2) / 2;
	c = std::max(a1, a2) - a;
	e = c / a;
	b = sqrt((1 - e * e) * a * a);
	data.SemiMajorAxis = a;
	data.Eccentricity = e;
	data.LongitudeOfTheAscendingNode = data1.LongitudeOfTheAscendingNode;
	data.Inclination = data1.Inclination;
	data.ArgumentOfPeriapsis = - data1.LongitudeOfTheAscendingNode + data2.LongitudeOfTheAscendingNode + data2.ArgumentOfPeriapsis + calculateE(data2.Eccentricity, calculateM(data2.MeanAnomaly, data2.SiderealOrbitalPeriod, global_t / 1000)) + (a1 < a2 ? 3.1415 : 0);
	data.q = fromEulerAngles({ 0, data.LongitudeOfTheAscendingNode, 0 }) * fromEulerAngles({ 0, 0, data.Inclination }) * fromEulerAngles({ 0, data.ArgumentOfPeriapsis, 0 });
	data.m = createRotation(data.q);
	tNow = global_t;
	data.SiderealOrbitalPeriod = calculateT(planets, star, data);
}

void calculateHomanOrbit3(PlanetData& data, Planets& planets, PlanetData& star, PlanetData& data1, PlanetData& data2, double global_t) {
	if (&data1 == 0 || &data2 == 0 || data1.SiderealOrbitalPeriod == 0 || data2.SiderealOrbitalPeriod == 0) return;
	float a{}, e{}, b{}, c{}, offset{}, a1{}, a2{}, t{};

	for (int i = 0; i < 10; i++) {
		a = data1.SemiMajorAxis;
		e = data1.Eccentricity;
		b = sqrt((1 - e * e) * a * a);
		c = e * a;
		offset = calculateOffsetFromAbsoluteF(data1, calculateOffsetAbsoluteF(data2, global_t + t * 500) - 3.1415);
		vec3 pos = data1.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };
		a1 = pos.length();

		a = data2.SemiMajorAxis;
		e = data2.Eccentricity;
		b = sqrt((1 - e * e) * a * a);
		c = e * a;
		offset = calculateOffset(data2, global_t + t * 500);
		pos = data2.m * vec3{ a * cos(offset) + c, 0, b * sin(offset) };
		a2 = pos.length();

		a = (a1 + a2) / 2;
		c = std::max(a1, a2) - a;
		e = c / a;
		b = sqrt((1 - e * e) * a * a);
		data.SemiMajorAxis = a;
		data.Eccentricity = e;
		data.LongitudeOfTheAscendingNode = data1.LongitudeOfTheAscendingNode;
		data.Inclination = data1.Inclination;
		data.ArgumentOfPeriapsis = -data1.LongitudeOfTheAscendingNode + data2.LongitudeOfTheAscendingNode + data2.ArgumentOfPeriapsis + calculateE(data2.Eccentricity, calculateM(data2.MeanAnomaly, data2.SiderealOrbitalPeriod, global_t / 1000 + t / 2)) + (a1 < a2 ? 3.1415 : 0);

		t = calculateT(planets, star, data);
		// добавлять ко времени марса ещё время подлета земли к точке старта
		// высчитывать время подлета земли к точке старта через среднюю аномалию
		// но перед этим сделать и вывести в текст глобальный таймер с момента старта проги
		// затем на траектории 3 проверить правильно ли считается время до манера

	}
	tNow = global_t;
	data.q = fromEulerAngles({ 0, data.LongitudeOfTheAscendingNode, 0 }) * fromEulerAngles({ 0, 0, data.Inclination }) * fromEulerAngles({ 0, data.ArgumentOfPeriapsis, 0 });
	data.m = createRotation(data.q);
	if (a1 > a2) data.MeanAnomaly = 3.1415;
	else data.MeanAnomaly = 0;
	data.SiderealOrbitalPeriod = t;
	tManeuver = calculateTtFromMAndM0(
		calculateM(data1.MeanAnomaly, data1.SiderealOrbitalPeriod, global_t / 1000), 
		calculateMFromOffset(data1, calculateOffsetFromAbsoluteF(data1, calculateOffsetAbsoluteF(data2, global_t + t * 500) - 3.1415)),
		data1.SiderealOrbitalPeriod);
}