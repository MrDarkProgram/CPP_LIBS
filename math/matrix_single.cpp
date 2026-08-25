#include "main.h"

mat4::mat4() {
	col0 = { 1, 0, 0, 0 };
	col1 = { 0, 1, 0, 0 };
	col2 = { 0, 0, 1, 0 };
	col3 = { 0, 0, 0, 1 };
}
mat4::mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) {
	this->col0 = col0;
	this->col1 = col1;
	this->col2 = col2;
	this->col3 = col3;
}
mat4::mat4(float a) {
	col0 = { a, 0, 0, 0 };
	col1 = { 0, a, 0, 0 };
	col2 = { 0, 0, a, 0 };
	col3 = { 0, 0, 0, a };
}
mat4 mat4::operator*(mat4 r) {
	mat4 Result;
	Result.col0 = col0 * r.col0[0] + col1 * r.col0[1] + col2 * r.col0[2] + col3 * r.col0[3];
	Result.col1 = col0 * r.col1[0] + col1 * r.col1[1] + col2 * r.col1[2] + col3 * r.col1[3];
	Result.col2 = col0 * r.col2[0] + col1 * r.col2[1] + col2 * r.col2[2] + col3 * r.col2[3];
	Result.col3 = col0 * r.col3[0] + col1 * r.col3[1] + col2 * r.col3[2] + col3 * r.col3[3];
	return Result;
}
vec4 mat4::operator*(vec4 r) {
	throw "not released!";
}
vec3 mat4::operator*(vec3 r) {
	vec3 v;
	v.x = col0.x * r.x + col1.x * r.y + col2.x * r.z + col3.x;
	v.y = col0.y * r.x + col1.y * r.y + col2.y * r.z + col3.y;
	v.z = col0.z * r.x + col1.z * r.y + col2.z * r.z + col3.z;
	return v;
}
bool mat4::operator==(mat4 r) {
	return col0 == r.col0 && col1 == r.col1 && col2 == r.col2 && col3 == r.col3;
}
bool mat4::operator!=(mat4 r) {
	return col0 != r.col0 && col1 != r.col1 && col2 != r.col2 && col3 != r.col3;
}
void mat4::operator*=(mat4 r) {
	col0 = col0 * r.col0[0] + col1 * r.col0[1] + col2 * r.col0[2] + col3 * r.col0[3];
	col1 = col0 * r.col1[0] + col1 * r.col1[1] + col2 * r.col1[2] + col3 * r.col1[3];
	col2 = col0 * r.col2[0] + col1 * r.col2[1] + col2 * r.col2[2] + col3 * r.col2[3];
	col3 = col0 * r.col3[0] + col1 * r.col3[1] + col2 * r.col3[2] + col3 * r.col3[3];
}
vec4 mat4::operator[](int i) {
	if (i == 0) return col0;
	if (i == 1) return col1;
	if (i == 2) return col2;
	if (i == 3) return col3;
	throw "Index out of range!";
}
mat4::operator mat4d() {
	return { col0, col1, col2, col3 };
}
mat4 createTranslate(vec3 v) {
	mat4 m;
	m.col3.x = v.x;
	m.col3.y = v.y;
	m.col3.z = v.z;
	return m;
}
mat4 createRotation(quaternion q) {
	mat4 matrix4{};

	float sqx = q.x * q.x;
	float sqy = q.y * q.y;
	float sqz = q.z * q.z;
	float sqw = q.w * q.w;

	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;

	float yz = q.y * q.z;
	float yw = q.y * q.w;

	float zw = q.z * q.w;

	float s2 = 2 / (sqx + sqy + sqz + sqw);

	matrix4.col0.x = 1 - (s2 * (sqy + sqz));
	matrix4.col1.y = 1 - (s2 * (sqx + sqz));
	matrix4.col2.z = 1 - (s2 * (sqx + sqy));

	matrix4.col0.y = s2 * (xy + zw);
	matrix4.col1.x = s2 * (xy - zw);

	matrix4.col2.x = s2 * (xz + yw);
	matrix4.col0.z = s2 * (xz - yw);

	matrix4.col2.y = s2 * (yz - xw);
	matrix4.col1.z = s2 * (yz + xw);

	matrix4.col3.w = 1;

	return matrix4;
}
mat4 createScale(vec3 v) {
	mat4 m;
	m.col0.x = v.x;
	m.col1.y = v.y;
	m.col2.z = v.z;
	return m;
}
mat4 lookAt(vec3 pos, vec3 at, vec3 up) {
	vec3 f(norm(at - pos));
	vec3 s(norm(cross(f, up)));
	vec3 u(cross(s, f));

	mat4 Result;
	Result.col0.x = s.x;
	Result.col1.x = s.y;
	Result.col2.x = s.z;
	Result.col0.y = u.x;
	Result.col1.y = u.y;
	Result.col2.y = u.z;
	Result.col0.z =-f.x;
	Result.col1.z =-f.y;
	Result.col2.z =-f.z;
	Result.col3.x =-dot(s, pos);
	Result.col3.y =-dot(u, pos);
	Result.col3.z = dot(f, pos);
	return Result;
}
mat4 perspective(float fov, float aspect, float near, float far) {
	float tanHalfFov = tan(fov / 2);

	mat4 Result{0};
	Result.col0.x = 1 / (aspect * tanHalfFov);
	Result.col1.y = 1 / (tanHalfFov);
	Result.col2.z = -(far + near) / (far - near);
	Result.col2.w = -1;
	Result.col3.z = -(2 * far * near) / (far - near);
	return Result;
}
