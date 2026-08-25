/// 
/// сделать возможность присвоения значения оператору []
/// 


#pragma once

#include <iostream>
#include <vector>

#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/math.lib")
#define MATH_API __declspec(dllimport)
#endif

#define PI 3.14159f

struct MATH_API vec2d;
struct MATH_API vec3d;
struct MATH_API vec4d;

struct MATH_API vec2 {
	float x;
	float y;

	vec2();
	vec2(float x, float y);

	vec2 operator+(vec2 r);
	vec2 operator-(vec2 r);
	vec2 operator+();
	vec2 operator-();
	vec2 operator*(vec2 r);
	vec2 operator*(float r);
	vec2 operator/(vec2 r);
	vec2 operator/(float r);
	bool operator==(vec2 r);
	bool operator!=(vec2 r);
	void operator+=(vec2 r);
	void operator-=(vec2 r);
	void operator*=(vec2 r);
	void operator*=(float r);
	void operator/=(vec2 r);
	void operator/=(float r);
	float operator[](int i);
	operator vec2d();

	float length();
	float length_squared();
	void norm();
};
MATH_API vec2 norm(vec2 v);
MATH_API std::ostream& operator<<(std::ostream& out, vec2 a);
MATH_API float dot(vec2 a, vec2 b);

struct MATH_API vec3 {
	float x;
	float y;
	float z;

	vec3();
	vec3(float x, float y, float z);
	vec3(vec2 xy, float z);
	
	vec3 operator+(vec3 r);
	vec3 operator-(vec3 r);
	vec3 operator+();
	vec3 operator-();
	vec3 operator*(vec3 r);
	vec3 operator*(float r);
	vec3 operator/(vec3 r);
	vec3 operator/(float r);
	bool operator==(vec3 r);
	bool operator!=(vec3 r);
	void operator+=(vec3 r);
	void operator-=(vec3 r);
	void operator*=(vec3 r);
	void operator*=(float r);
	void operator/=(vec3 r);
	void operator/=(float r);
	float operator[](int i);
	operator vec3d();

	float length();
	float length_squared();
	void norm();
};
MATH_API vec3 norm(vec3 v);
MATH_API std::ostream& operator<<(std::ostream& out, vec3 a);
MATH_API float dot(vec3 a, vec3 b);
MATH_API vec3 cross(vec3 a, vec3 b);
MATH_API float triple(vec3 a, vec3 b, vec3 c);

struct MATH_API vec4 {
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(float x, float y, float z, float w);
	vec4(vec2 xy, float z, float w);
	vec4(vec3 xy, float z);

	vec4 operator+(vec4 r);
	vec4 operator-(vec4 r);
	vec4 operator+();
	vec4 operator-();
	vec4 operator*(vec4 r);
	vec4 operator*(float r);
	vec4 operator/(vec4 r);
	vec4 operator/(float r);
	bool operator==(vec4 r);
	bool operator!=(vec4 r);
	void operator+=(vec4 r);
	void operator-=(vec4 r);
	void operator*=(vec4 r);
	void operator*=(float r);
	void operator/=(vec4 r);
	void operator/=(float r);
	float operator[](int i);
	operator vec4d();

	float length();
	float length_squared();
	void norm();
};
MATH_API vec4 norm(vec4 v);
MATH_API std::ostream& operator<<(std::ostream& out, vec4 a);
MATH_API float dot(vec4 a, vec4 b);

struct MATH_API vec2d {
	double x;
	double y;

	vec2d();
	vec2d(double x, double y);

	vec2d operator+(vec2d r);
	vec2d operator-(vec2d r);
	vec2d operator+();
	vec2d operator-();
	vec2d operator*(vec2d r);
	vec2d operator*(double r);
	vec2d operator/(vec2d r);
	vec2d operator/(double r);
	bool operator==(vec2d r);
	bool operator!=(vec2d r);
	void operator+=(vec2d r);
	void operator-=(vec2d r);
	void operator*=(vec2d r);
	void operator*=(double r);
	void operator/=(vec2d r);
	void operator/=(double r);
	double operator[](int i);
	operator vec2();

	double length();
	double length_squared();
	void norm();
};
MATH_API vec2d norm(vec2d v);
MATH_API std::ostream& operator<<(std::ostream& out, vec2d a);
MATH_API double dot(vec2d a, vec2d b);

struct MATH_API vec3d {
	double x;
	double y;
	double z;

	vec3d();
	vec3d(double x, double y, double z);
	vec3d(vec2d xy, double z);

	vec3d operator+(vec3d r);
	vec3d operator-(vec3d r);
	vec3d operator+();
	vec3d operator-();
	vec3d operator*(vec3d r);
	vec3d operator*(double r);
	vec3d operator/(vec3d r);
	vec3d operator/(double r);
	bool operator==(vec3d r);
	bool operator!=(vec3d r);
	void operator+=(vec3d r);
	void operator-=(vec3d r);
	void operator*=(vec3d r);
	void operator*=(double r);
	void operator/=(vec3d r);
	void operator/=(double r);
	double operator[](int i);
	operator vec3();

	double length();
	double length_squared();
	void norm();
};
MATH_API vec3d norm(vec3d v);
MATH_API std::ostream& operator<<(std::ostream& out, vec3d a);
MATH_API double dot(vec3d a, vec3d b);
MATH_API vec3d cross(vec3d a, vec3d b);
MATH_API double triple(vec3d a, vec3d b, vec3d c);

struct MATH_API vec4d {
	double x;
	double y;
	double z;
	double w;

	vec4d();
	vec4d(double x, double y, double z, double w);
	vec4d(vec2d xy, double z, double w);
	vec4d(vec3d xy, double z);

	vec4d operator+(vec4d r);
	vec4d operator-(vec4d r);
	vec4d operator+();
	vec4d operator-();
	vec4d operator*(vec4d r);
	vec4d operator*(double r);
	vec4d operator/(vec4d r);
	vec4d operator/(double r);
	bool operator==(vec4d r);
	bool operator!=(vec4d r);
	void operator+=(vec4d r);
	void operator-=(vec4d r);
	void operator*=(vec4d r);
	void operator*=(double r);
	void operator/=(vec4d r);
	void operator/=(double r);
	double operator[](int i);
	operator vec4();

	double length();
	double length_squared();
	void norm();
};
MATH_API vec4d norm(vec4d v);
MATH_API std::ostream& operator<<(std::ostream& out, vec4d a);
MATH_API double dot(vec4d a, vec4d b);

struct MATH_API quaternion {
	float x;
	float y;
	float z;
	float w;

	quaternion();
	quaternion(float x, float y, float z, float w);
	quaternion(vec3 angles);
	quaternion(vec3 axis, float angle);

	quaternion operator*(quaternion r);
	bool operator==(quaternion r);
	bool operator!=(quaternion r);
	void operator*=(quaternion r);
	float operator[](int i);

	float length();
	float length_squared();
	quaternion norm();
	void norm_this();
	vec3 toEulerAngles();
	vec4 toAxisAngle();
};
MATH_API quaternion fromEulerAngles(vec3 angles);
MATH_API quaternion fromAxisAngle(vec3 axis, float angle);
MATH_API quaternion inverse(quaternion q);
MATH_API std::ostream& operator<<(std::ostream& out, quaternion a);

struct MATH_API mat4d;

struct MATH_API mat4 {
	vec4 col0;
	vec4 col1;
	vec4 col2;
	vec4 col3;

	mat4();
	mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3);
	mat4(float a);

	mat4 operator*(mat4 r);
	vec4 operator*(vec4 r);
	vec3 operator*(vec3 r);
	bool operator==(mat4 r);
	bool operator!=(mat4 r);
	void operator*=(mat4 r);
	vec4 operator[](int i);
	operator mat4d();
};
MATH_API mat4 createTranslate(vec3 v);
MATH_API mat4 createRotation(quaternion q);
MATH_API mat4 createScale(vec3 v);
MATH_API mat4 lookAt(vec3 pos, vec3 at, vec3 up);
MATH_API mat4 perspective(float fovy, float aspect, float zNear, float zFar);

struct MATH_API mat4d {
	vec4d col0;
	vec4d col1;
	vec4d col2;
	vec4d col3;

	mat4d();
	mat4d(vec4d col0, vec4d col1, vec4d col2, vec4d col3);
	mat4d(double a);

	mat4d operator*(mat4d r);
	vec4d operator*(vec4d r);
	vec3d operator*(vec3d r);
	bool operator==(mat4d r);
	bool operator!=(mat4d r);
	void operator*=(mat4d r);
	vec4d operator[](int i);
	operator mat4();
};
MATH_API mat4d createTranslate(vec3d v);
MATH_API mat4d createScale(vec3d v);
MATH_API mat4d lookAt(vec3d pos, vec3d at, vec3d up);

struct tetrahedron
{
	vec3 a;
	vec3 b;
	vec3 c;
	vec3 d;
	tetrahedron* abc;
	tetrahedron* abd;
	tetrahedron* acd;
	tetrahedron* bcd;
};
using tetrahedrons = std::vector<tetrahedron>;

struct triangle
{
	vec3 a;
	vec3 b;
	vec3 c;
};
using trianglesStructure = std::vector<triangle>;
using trianglesS = trianglesStructure;

// vec3 pos;
// vec3 norm;
// vec4 color;
// vec2 tex;
// unsigned data;
struct vertex {
	vec3 pos;
	vec3 norm;
	vec4 color;
	vec2 tex;
	unsigned data;
};

// vec3 pos;
// vec3 norm;
// vec4 color;
// vec2 tex;
// unsigned data;
using vertexes = std::vector<vertex>;

enum drawMode : uint8_t {
	points = 0,
	lines = 1,
	triangles = 2,
	dyn_points = 4,
	dyn_lines = 5,
	dyn_triangles = 6
};

struct MATH_API object {
	static unsigned now_id;

	vec3d pos{};
	vec3 center{};
	quaternion rot{};
	vec3 scl{};
	drawMode mode{};
	bool enable = true;
	bool alpha = false;
	bool select = false;
	unsigned id{};
	vec4 color{};
	vertexes vert{};

	object();

	void addTetrahedron(tetrahedrons ts, vec4 color, drawMode mode);
	void addTriangles(trianglesS ts, vec4 color, drawMode mode);
	void addTriangles(trianglesS ts, vec4 color, vec3 center, drawMode mode);
};