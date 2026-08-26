#pragma once
#include "main.h"

trianglesS generateSphere(unsigned subdivides) {
	float f2 = (1 + sqrtf(5)) / 4;
	float i2 = 1.0f / 2;
	vec3 v0{ 0, 0, 0 };
	vec3 v1{ 0, i2, f2 };
	vec3 v2{ 0, -i2, f2 };
	vec3 v3{ 0, i2, -f2 };
	vec3 v4{ 0, -i2, -f2 };
	vec3 v5{ i2, f2, 0 };
	vec3 v6{ -i2, f2, 0 };
	vec3 v7{ i2, -f2, 0 };
	vec3 v8{ -i2, -f2, 0 };
	vec3 v9{ f2, 0, i2 };
	vec3 vA{ -f2, 0, i2 };
	vec3 vB{ f2, 0, -i2 };
	vec3 vC{ -f2, 0, -i2 };
	trianglesS ts{};
	ts.push_back({ v1, v2, v9 }); // 0
	ts.push_back({ v1, vA, v2 }); // 1
	ts.push_back({ v1, v5, v6 }); // 2
	ts.push_back({ v1, v9, v5 }); // 3
	ts.push_back({ v1, v6, vA }); // 4
	ts.push_back({ v2, v8, v7 }); // 5
	ts.push_back({ v2, v7, v9 }); // 6
	ts.push_back({ v2, vA, v8 }); // 7
	ts.push_back({ v3, vB, v4 }); // 8
	ts.push_back({ v3, v4, vC }); // 9
	ts.push_back({ v3, v6, v5 }); // 10
	ts.push_back({ v3, v5, vB }); // 11
	ts.push_back({ v3, vC, v6 }); // 12
	ts.push_back({ v4, v7, v8 }); // 13
	ts.push_back({ v4, vB, v7 }); // 14
	ts.push_back({ v4, v8, vC }); // 15
	ts.push_back({ v5, v9, vB }); // 16
	ts.push_back({ v7, vB, v9 }); // 17
	ts.push_back({ v8, vA, vC }); // 18
	ts.push_back({ vA, v6, vC }); // 19

	trianglesS ts2{};
	for (int i = 0; i < subdivides; i++) {
		for(triangle& t : ts)
		{
			float r = sqrtf((5 + sqrtf(5)) / 8);
			float l = (t.a - t.b).length();
			vec3 ab = (t.a + t.b) / 2;
			vec3 ac = (t.a + t.c) / 2;
			vec3 bc = (t.b + t.c) / 2;
			if (r - ab.length() < l / 7) {
				ab = norm(ab) * r;
			}
			if (r - ac.length() < l / 7) {
				ac = norm(ac) * r;
			}
			if (r - bc.length() < l / 7) {
				bc = norm(bc) * r;
			}
			ts2.push_back({ t.a, ab, ac });
			ts2.push_back({ t.b, bc, ab });
			ts2.push_back({ t.c, ac, bc });
			ts2.push_back({ ab, bc, ac });
		}
		ts = ts2;
		ts2.clear();
	}

	return ts;
}

trianglesS generateSphereAndRing(unsigned subdivides, float r1, float r2) {
	trianglesS ts = generateSphere(subdivides);
	if (r1 != 0 && r2 != 0) {
		float angle = 6.2832 / subdivides / 12;
		for (int i = 0; i < subdivides * 12; i++) {
			vec3 pos1 = { r1 * cos(i * angle), 0, r1 * sin(i * angle) };
			vec3 pos2 = { r2 * cos(i * angle), 0, r2 * sin(i * angle) };
			vec3 pos3 = { r1 * cos((i + 1) * angle), 0, r1 * sin((i + 1) * angle) };
			vec3 pos4 = { r2 * cos((i + 1) * angle), 0, r2 * sin((i + 1) * angle) };
			ts.push_back({ pos1, pos2, pos3 });
			ts.push_back({ pos3, pos2, pos4 });
			ts.push_back({ pos1, pos3, pos2 });
			ts.push_back({ pos2, pos3, pos4 });
		}
	}
	return ts;
}

vertexes drawEllipse(float a, float b, unsigned lines_count) {
	vertexes verts = {};

	float step = 2 * 3.1415f / lines_count;
	
	for (int i = 0; i < lines_count; i++) {
		float t = i * step;
		float t1 = (i + 1) * step;
		verts.push_back({ {a * cos(t), 0, b * sin(t)}, {}, {1, 1, 1, 1}, {}, 0 });
		verts.push_back({ {a * cos(t1), 0, b * sin(t1)}, {}, {1, 1, 1, 1}, {}, 0 });
	}

	return verts;
}

vertexes drawOrbit(PlanetData data, unsigned lines_count) {
	vertexes verts = {};

	float a = data.SemiMajorAxis;
	float e = data.Eccentricity;
	float b = sqrt((1 - e * e) * a * a);
	float c = e * a;
	float step = 2 * 3.1415f / lines_count;
	vec4 color = { data.ColorR, data.ColorG, data.ColorB, 1 };

	for (int i = 0; i < lines_count; i++) {
		float t = i * step;
		float t1 = (i + 1) * step;
		verts.push_back({ data.m * vec3{ a * cos(t) + c, 0, b * sin(t) }, {}, color, {}, 0 });
		verts.push_back({ data.m * vec3{ a * cos(t1) + c, 0, b * sin(t1) }, {}, color, {}, 0 });
	}
	//verts.push_back({ data.m * vec3{0, 0, a * (1 - e * e)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{0, 0, a * (e * e - 1)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{- a + c, 0, 0}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{a + c, 0, 0}, {}, color / 2, {}, 0 });

	return verts;
}

float ellipseLength(float a, float b) {
	return 4 * (3.1415 * a * b + (a - b) * (a - b)) / (a + b);
}

vertexes drawOrbit(PlanetData data) {
	vertexes verts = {};

	float a = data.SemiMajorAxis;
	float e = data.Eccentricity;
	float b = sqrt((1 - e * e) * a * a);
	float c = e * a;
	float lines_count = ellipseLength(a, b) / 0.5;
	float step = 2 * 3.1415f / lines_count;
	vec4 color = { data.ColorR, data.ColorG, data.ColorB, 1 };

	for (int i = 0; i < lines_count; i++) {
		float t = i * step;
		float t1 = (i + 1) * step;
		verts.push_back({ data.m * vec3{ a * cos(t) + c, 0, b * sin(t) }, {}, color, {}, 0 });
		verts.push_back({ data.m * vec3{ a * cos(t1) + c, 0, b * sin(t1) }, {}, color, {}, 0 });
	}
	//verts.push_back({ data.m * vec3{0, 0, a * (1 - e * e)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{0, 0, a * (e * e - 1)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{-a + c, 0, 0}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{a + c, 0, 0}, {}, color / 2, {}, 0 });

	return verts;
}

vertexes drawOrbit05(PlanetData data) {
	vertexes verts = {};

	float a = data.SemiMajorAxis;
	float e = data.Eccentricity;
	float b = sqrt((1 - e * e) * a * a);
	float c = e * a;
	float lines_count = ellipseLength(a, b) / 0.5;
	float step = 2 * 3.1415f / lines_count;
	vec4 color = { data.ColorR, data.ColorG, data.ColorB, 1 };

	for (int i = 0; i < lines_count / 2; i++) {
		float t = i * step;
		float t1 = (i + 1) * step;
		verts.push_back({ data.m * vec3{ a * cos(t) + c, 0, b * sin(t) }, {}, color, {}, 0 });
		verts.push_back({ data.m * vec3{ a * cos(t1) + c, 0, b * sin(t1) }, {}, color, {}, 0 });
	}
	//verts.push_back({ data.m * vec3{0, 0, a * (1 - e * e)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{0, 0, a * (e * e - 1)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{-a + c, 0, 0}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{a + c, 0, 0}, {}, color / 2, {}, 0 });

	return verts;
}

vertexes drawOrbit50(PlanetData data) {
	vertexes verts = {};

	float a = data.SemiMajorAxis;
	float e = data.Eccentricity;
	float b = sqrt((1 - e * e) * a * a);
	float c = e * a;
	float lines_count = ellipseLength(a, b) / 0.5;
	float step = 2 * 3.1415f / lines_count;
	vec4 color = { data.ColorR, data.ColorG, data.ColorB, 1 };

	for (int i = lines_count / 2; i < lines_count; i++) {
		float t = i * step;
		float t1 = (i + 1) * step;
		verts.push_back({ data.m * vec3{ a * cos(t) + c, 0, b * sin(t) }, {}, color, {}, 0 });
		verts.push_back({ data.m * vec3{ a * cos(t1) + c, 0, b * sin(t1) }, {}, color, {}, 0 });
	}
	//verts.push_back({ data.m * vec3{0, 0, a * (1 - e * e)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{0, 0, a * (e * e - 1)}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{-a + c, 0, 0}, {}, color / 2, {}, 0 });
	//verts.push_back({ data.m * vec3{a + c, 0, 0}, {}, color / 2, {}, 0 });

	return verts;
}