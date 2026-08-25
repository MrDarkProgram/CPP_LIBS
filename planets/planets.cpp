#include "main.h"

void Planet::Create(unsigned subSph) {

	// генерируем геометрию планеты и параллельно заполняем массивы
	tetrahedrons ts = generateIcosahedron();
	for (int i = 0; i < ts.size(); i++) {
		slices.push_back({});
		tetrahedrons ts1 = subdivideTetrahedronsToSphere({ ts[i] }, subSph);
		setLinks(ts1);
		for (int j = 0; j < ts1.size(); j++) {
			slices.back().push_back(*(Unit*)&(ts1[j]));
		}
		obj.addTetrahedron(ts1, { 1, 1, 1, 1 }, triangles);
	}
	obj.scl = { 5, 5, 5 };
	obj.pos = { 0, 0, 10 };
}