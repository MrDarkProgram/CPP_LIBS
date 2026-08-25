#include "main.h"

unsigned object::now_id{0};

object::object() {
	now_id++;
	id = now_id;

	pos = {};
	center = {};
	rot = {};
	scl = {1, 1, 1};
	mode = {};
	vert = {};
}

void object::addTetrahedron(tetrahedrons ts, vec4 color, drawMode mode) {
	this->mode = mode;
	switch (mode)
	{
	case points:
	case dyn_points:
		break;
	case lines:
	case dyn_lines:
		break;
	case triangles:
	case dyn_triangles:
		for (tetrahedron &t : ts) {
			vec3 n;
			if (!t.abc) {
				n = norm(cross(t.a - t.c, t.b - t.c));
				vert.push_back({ t.a, n, color, {}, 0 });
				vert.push_back({ t.b, n, color, {}, 0 });
				vert.push_back({ t.c, n, color, {}, 0 });
			}

			if (!t.abd) {
				n = norm(cross(t.b - t.d, t.a - t.d));
				vert.push_back({ t.b, n, color, {}, 0 });
				vert.push_back({ t.a, n, color, {}, 0 });
				vert.push_back({ t.d, n, color, {}, 0 });
			}

			if (!t.acd) {
				n = norm(cross(t.d - t.c, t.a - t.c));
				vert.push_back({ t.d, n, color, {}, 0 });
				vert.push_back({ t.a, n, color, {}, 0 });
				vert.push_back({ t.c, n, color, {}, 0 });
			}

			if (!t.bcd) {
				n = norm(cross(t.b - t.c, t.d - t.c));
				vert.push_back({ t.b, n, color, {}, 0 });
				vert.push_back({ t.d, n, color, {}, 0 });
				vert.push_back({ t.c, n, color, {}, 0 });
			}
		}
		break;
	default:
		break;
	}
}

void object::addTriangles(trianglesS ts, vec4 color, drawMode mode)
{
	this->mode = mode;
	switch (mode)
	{
	case points:
	case dyn_points:
		break;
	case lines:
	case dyn_lines:
		break;
	case triangles:
	case dyn_triangles:
		for (triangle& t : ts) {
			vec3 n = norm(cross(t.a - t.c, t.b - t.c));
			vert.push_back({ t.a, n, color, {}, 0 });
			vert.push_back({ t.b, n, color, {}, 0 });
			vert.push_back({ t.c, n, color, {}, 0 });
		}
		break;
	default:
		break;
	}
}

void object::addTriangles(trianglesS ts, vec4 color, vec3 center, drawMode mode)
{
	this->mode = mode;
	switch (mode)
	{
	case points:
	case dyn_points:
		break;
	case lines:
	case dyn_lines:
		break;
	case triangles:
	case dyn_triangles:
		for (triangle& t : ts) {
			vert.push_back({ t.a, t.a - center, color, {}, 0 });
			vert.push_back({ t.b, t.b - center, color, {}, 0 });
			vert.push_back({ t.c, t.c - center, color, {}, 0 });
		}
		break;
	default:
		break;
	}
}
