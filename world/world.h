#pragma once

#include "../math/math.h";

#ifdef WORLD_EXPORTS
#define WORLD_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/world.lib")
#define WORLD_API __declspec(dllimport)
#endif

enum WORLD_API Matter : unsigned char {
	none,
	something,
};

constexpr unsigned cloudSize = 48;

class WORLD_API DotCloud {
	Matter cloud[cloudSize][cloudSize][cloudSize]{};
	vec3d pos;
	quaternion rot;
	vec3 scl{ 1, 1, 1 };
	vec3 selected{ -1, -1, -1 };
public:
	DotCloud();
	void getDotRef(vec3 pos, Matter& matter);
	Matter getDot(vec3 pos);
	void setDot(vec3 pos, Matter matter);
	object generatePointModel() const;
	object generateLineModel() const;
	object generatePolygonModel() const;
	vec3 checkRay(vec3 startPos, vec3 forward, float dist) const;
	void checkRay(vec3 startPos, vec3 forward, float dist, vec3& obj, vec3& preObj) const;
	vec3 checkRayPre(vec3 startPos, vec3 forward, float dist) const;
	vec3 getSelect();
	void setSelect(vec3 select);
};