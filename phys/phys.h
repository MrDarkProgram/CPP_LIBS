#pragma once

#include "../math/math.h"

#ifdef PHYS_EXPORTS
#define PHYS_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/phys.lib")
#define PHYS_API __declspec(dllimport)
#endif

PHYS_API void initPhys();
PHYS_API void createBody(object& obj);
PHYS_API void createSphereBody(object& obj);
//PHYS_API void createSphereBodyG(vec3d pos, vec3 scl = { 1, 1, 1 }, vec3 vel = {});
PHYS_API void addBodyVel(int body_id, vec3 vel);
PHYS_API unsigned testRay(vec3d start, vec3d end);
PHYS_API void update(float time);
PHYS_API void updateG(float time);
PHYS_API void updateObjectData(object& obj);
PHYS_API void createObjectsG(vec3d from, vec3 to, float vel_max, float angular_vel_factor, int n);