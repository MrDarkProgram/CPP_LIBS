#pragma once

#include "../math/math.h"

#include <vector>

#ifdef MESH_GENERATOR_EXPORTS
#define MESH_GENERATOR_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/mesh_generator.lib")
#define MESH_GENERATOR_API __declspec(dllimport)
#endif

MESH_GENERATOR_API tetrahedrons subdivideTetrahedron(tetrahedron t);
MESH_GENERATOR_API tetrahedrons subdivideTetrahedrons(tetrahedrons ts);
MESH_GENERATOR_API tetrahedrons subdivideTetrahedrons(tetrahedrons ts, int steps);
MESH_GENERATOR_API tetrahedrons subdivideTetrahedronToSphere(tetrahedron t);
MESH_GENERATOR_API tetrahedrons subdivideTetrahedronsToSphere(tetrahedrons ts);
MESH_GENERATOR_API tetrahedrons subdivideTetrahedronsToSphere(tetrahedrons ts, int steps);
MESH_GENERATOR_API tetrahedrons fractalGenerator(tetrahedron t);
MESH_GENERATOR_API tetrahedrons fractalGenerator(tetrahedrons ts);
MESH_GENERATOR_API tetrahedrons fractalGenerator(tetrahedrons ts, int steps);
MESH_GENERATOR_API tetrahedrons generateIcosahedron();
MESH_GENERATOR_API tetrahedrons subdivideIcosahedron(tetrahedrons ts);
MESH_GENERATOR_API tetrahedrons subdivideIcosahedron(tetrahedrons ts, int steps);
MESH_GENERATOR_API void setLinks(tetrahedrons& ts);