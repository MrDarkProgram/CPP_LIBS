#pragma once

#define IS_RP3D_DOUBLE_PRECISION_ENABLED
#include <reactphysics3d/reactphysics3d.h>
namespace rp = reactphysics3d;

#include "../mesh_generator/mesh_generator.h"
#include "../opengl_graphics/opengl_graphics.h"
#include <map>
#include <unordered_map>
#include <random>

#define PHYS_EXPORTS
#include "phys.h"

#define TORPVEC3D *(rp::Vector3*)&
#define TOVEC3D *(vec3d*)&
rp::Vector3 toRpVec3(vec3 q) {
	double qd[]{ q.x, q.y, q.z };
	return *(rp::Vector3*)&qd;
}
vec3 toVec3(rp::Vector3 q) {
	float qd[]{ q.x, q.y, q.z };
	return *(vec3*)&qd;
}
rp::Quaternion toRpQuat(quaternion q) {
	double qd[]{ q.x, q.y, q.z, q.w };
	return *(rp::Quaternion*)&qd;
}
quaternion toQuat(rp::Quaternion q) {
	float qd[]{ q.x, q.y, q.z, q.w };
	return *(quaternion*)&qd;
}

rp::PhysicsCommon physCommon;
rp::PhysicsWorld* physWorld;