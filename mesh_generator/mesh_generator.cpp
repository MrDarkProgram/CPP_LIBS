#include "main.h"

tetrahedrons subdivideTetrahedron(tetrahedron t) {
	tetrahedrons ts{};
	vec3 ab = (t.a + t.b) / 2;
	vec3 ac = (t.a + t.c) / 2;
	vec3 ad = (t.a + t.d) / 2;
	vec3 bc = (t.b + t.c) / 2;
	vec3 bd = (t.b + t.d) / 2;
	vec3 cd = (t.c + t.d) / 2;
	ts.push_back({ t.a, ab, ac, ad });
	ts.push_back({ t.b, bc, ab, bd });
	ts.push_back({ t.c, ac, bc, cd });
	ts.push_back({ t.d, bd, ad, cd });
	ts.push_back({ ab, ac, ad, cd });
	ts.push_back({ ab, bc, ac, cd });
	ts.push_back({ ab, bd, bc, cd });
	ts.push_back({ ab, ad, bd, cd });
	return ts;
}

tetrahedrons subdivideTetrahedrons(tetrahedrons ts) {
	tetrahedrons ts2{};
	for (tetrahedron& t2 : ts) {
		tetrahedrons ts3 = subdivideTetrahedron(t2);
		ts2.insert(ts2.end(), ts3.begin(), ts3.end());
	}
	return ts2;
}

tetrahedrons subdivideTetrahedrons(tetrahedrons ts, int steps) {
	for (int i = 0; i < steps; i++) {
		ts = subdivideTetrahedrons(ts);
	}
	return ts;
}

tetrahedrons subdivideTetrahedronToSphere(tetrahedron t) {
	tetrahedrons ts{};
	float r = sqrtf((5 + sqrtf(5)) / 8);
	float l = (t.a - t.b).length();
	vec3 ab = (t.a + t.b) / 2;
	vec3 ac = (t.a + t.c) / 2;
	vec3 ad = (t.a + t.d) / 2;
	vec3 bc = (t.b + t.c) / 2;
	vec3 bd = (t.b + t.d) / 2;
	vec3 cd = (t.c + t.d) / 2;
	if (r - ab.length() < l / 7) {
		ab = norm(ab) * r;
	}
	if (r - ac.length() < l / 7) {
		ac = norm(ac) * r;
	}
	if (r - bc.length() < l / 7) {
		bc = norm(bc) * r;
	}
	ts.push_back({ t.a, ab, ac, ad });
	ts.push_back({ t.b, bc, ab, bd });
	ts.push_back({ t.c, ac, bc, cd });
	ts.push_back({ t.d, bd, ad, cd });
	ts.push_back({ ab, ac, ad, cd });
	ts.push_back({ ab, bc, ac, cd });
	ts.push_back({ ab, bd, bc, cd });
	ts.push_back({ ab, ad, bd, cd });
	return ts;
}

tetrahedrons subdivideTetrahedronsToSphere(tetrahedrons ts) {
	tetrahedrons ts2{};
	for (tetrahedron& t2 : ts) {
		tetrahedrons ts3 = subdivideTetrahedronToSphere(t2);
		ts2.insert(ts2.end(), ts3.begin(), ts3.end());
	}
	return ts2;
}

tetrahedrons subdivideTetrahedronsToSphere(tetrahedrons ts, int steps) {
	for (int i = 0; i < steps; i++) {
		ts = subdivideTetrahedronsToSphere(ts);
	}
	return ts;
}

tetrahedrons fractalGenerator(tetrahedron t) {
	tetrahedrons ts{};
	vec3 ab = (t.a + t.b) / 2;
	vec3 ac = (t.a + t.c) / 2;
	vec3 ad = (t.a + t.d) / 2;
	vec3 bc = (t.b + t.c) / 2;
	vec3 bd = (t.b + t.d) / 2;
	vec3 cd = (t.c + t.d) / 2;
	ts.push_back({ t.a, ab, ac, ad });
	ts.push_back({ t.b, ab, bc, bd });
	ts.push_back({ t.c, ac, bc, cd });
	ts.push_back({ t.d, ad, bd, cd });
	return ts;
}

tetrahedrons fractalGenerator(tetrahedrons ts) {
	tetrahedrons ts2{};
	for (tetrahedron& t2 : ts) {
		tetrahedrons ts3 = fractalGenerator(t2);
		ts2.insert(ts2.end(), ts3.begin(), ts3.end());
	}
	return ts2;
}

tetrahedrons fractalGenerator(tetrahedrons ts, int steps) {
	for (int i = 0; i < steps; i++) {
		ts = fractalGenerator(ts);
	}
	return ts;
}

tetrahedrons generateIcosahedron() {
	float f2 = (1 + sqrtf(5)) / 4;
	float i2 = 1.0f / 2;
	vec3 v0{0, 0, 0};
	vec3 v1{0, i2, f2};
	vec3 v2{0, -i2, f2};
	vec3 v3{0, i2, -f2};
	vec3 v4{0, -i2, -f2};
	vec3 v5{i2, f2, 0};
	vec3 v6{-i2, f2, 0};
	vec3 v7{i2, -f2, 0};
	vec3 v8{-i2, -f2, 0};
	vec3 v9{f2, 0, i2};
	vec3 vA{-f2, 0, i2};
	vec3 vB{f2, 0, -i2};
	vec3 vC{-f2, 0, -i2};
	tetrahedrons ts{};
	ts.push_back({ v1, v2, v9 ,v0 }); // 0
	ts.push_back({ v1, vA, v2 ,v0 }); // 1
	ts.push_back({ v1, v5, v6 ,v0 }); // 2
	ts.push_back({ v1, v9, v5 ,v0 }); // 3
	ts.push_back({ v1, v6, vA ,v0 }); // 4
	ts.push_back({ v2, v8, v7 ,v0 }); // 5
	ts.push_back({ v2, v7, v9 ,v0 }); // 6
	ts.push_back({ v2, vA, v8 ,v0 }); // 7
	ts.push_back({ v3, vB, v4 ,v0 }); // 8
	ts.push_back({ v3, v4, vC ,v0 }); // 9
	ts.push_back({ v3, v6, v5 ,v0 }); // 10
	ts.push_back({ v3, v5, vB ,v0 }); // 11
	ts.push_back({ v3, vC, v6 ,v0 }); // 12
	ts.push_back({ v4, v7, v8 ,v0 }); // 13
	ts.push_back({ v4, vB, v7 ,v0 }); // 14
	ts.push_back({ v4, v8, vC ,v0 }); // 15
	ts.push_back({ v5, v9, vB ,v0 }); // 16
	ts.push_back({ v7, vB, v9 ,v0 }); // 17
	ts.push_back({ v8, vA, vC ,v0 }); // 18
	ts.push_back({ vA, v6, vC ,v0 }); // 19
	return ts;
}

tetrahedrons subdivideIcosahedron(tetrahedrons ts) {
	tetrahedrons ts2{};
	for (tetrahedron t : ts) {
		vec3 ab = (t.a + t.b) / 2;
		vec3 ac = (t.a + t.c) / 2;
		vec3 bc = (t.b + t.c) / 2;
		float r = sqrtf((5 + sqrtf(5)) / 8);
		ab = norm(ab) * r;
		ac = norm(ac) * r;
		bc = norm(bc) * r;
		ts2.push_back({ {0, 0, 0}, t.a, ab, ac });
		ts2.push_back({ {0, 0, 0}, t.b, ab, bc });
		ts2.push_back({ {0, 0, 0}, t.c, ac, bc });
		ts2.push_back({ {0, 0, 0}, ab, ac, bc });
	}
	return ts2;
}

tetrahedrons subdivideIcosahedron(tetrahedrons ts, int steps) {
	for (int i = 0; i < steps; i++) {
		ts = subdivideIcosahedron(ts);
	}
	return ts;
}

void setLinks(tetrahedrons& ts) {
	for (int i = 0; i < ts.size(); i++) {
		for (int j = 0; j < ts.size(); j++) {
			if ((ts[i].a == ts[j].a || ts[i].a == ts[j].b || ts[i].a == ts[j].c) && (ts[i].b == ts[j].a || ts[i].b == ts[j].b || ts[i].b == ts[j].c)) {
				ts[i].abd = &ts[j];
			}
			if ((ts[i].a == ts[j].a || ts[i].a == ts[j].b || ts[i].a == ts[j].c) && (ts[i].c == ts[j].a || ts[i].c == ts[j].b || ts[i].c == ts[j].c)) {
				ts[i].acd = &ts[j];
			}
			if ((ts[i].b == ts[j].a || ts[i].b == ts[j].b || ts[i].b == ts[j].c) && (ts[i].c == ts[j].a || ts[i].c == ts[j].b || ts[i].c == ts[j].c)) {
				ts[i].bcd = &ts[j];
			}
		}
	}

}