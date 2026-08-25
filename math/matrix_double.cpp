#include "main.h"

mat4d::mat4d() {
	col0 = { 1, 0, 0, 0 };
	col1 = { 0, 1, 0, 0 };
	col2 = { 0, 0, 1, 0 };
	col3 = { 0, 0, 0, 1 };
}
mat4d::mat4d(vec4d col0, vec4d col1, vec4d col2, vec4d col3) {
	this->col0 = col0;
	this->col1 = col1;
	this->col2 = col2;
	this->col3 = col3;
}
mat4d::mat4d(double a) {
	col0 = { a, 0, 0, 0 };
	col1 = { 0, a, 0, 0 };
	col2 = { 0, 0, a, 0 };
	col3 = { 0, 0, 0, a };
}
mat4d mat4d::operator*(mat4d r) {
	mat4d Result;
	Result.col0 = col0 * r.col0[0] + col1 * r.col0[1] + col2 * r.col0[2] + col3 * r.col0[3];
	Result.col1 = col0 * r.col1[0] + col1 * r.col1[1] + col2 * r.col1[2] + col3 * r.col1[3];
	Result.col2 = col0 * r.col2[0] + col1 * r.col2[1] + col2 * r.col2[2] + col3 * r.col2[3];
	Result.col3 = col0 * r.col3[0] + col1 * r.col3[1] + col2 * r.col3[2] + col3 * r.col3[3];
	return Result;
}
vec4d mat4d::operator*(vec4d r) {
	throw "not released!";
}
vec3d mat4d::operator*(vec3d r) {
	vec3d v;
	v.x = col0.x * r.x + col1.x * r.y + col2.x * r.z + col3.x;
	v.y = col0.y * r.x + col1.y * r.y + col2.y * r.z + col3.y;
	v.z = col0.z * r.x + col1.z * r.y + col2.z * r.z + col3.z;
	return v;
}
bool mat4d::operator==(mat4d r) {
	return col0 == r.col0 && col1 == r.col1 && col2 == r.col2 && col3 == r.col3;
}
bool mat4d::operator!=(mat4d r) {
	return col0 != r.col0 && col1 != r.col1 && col2 != r.col2 && col3 != r.col3;
}
void mat4d::operator*=(mat4d r) {
	col0 = col0 * r.col0[0] + col1 * r.col0[1] + col2 * r.col0[2] + col3 * r.col0[3];
	col1 = col0 * r.col1[0] + col1 * r.col1[1] + col2 * r.col1[2] + col3 * r.col1[3];
	col2 = col0 * r.col2[0] + col1 * r.col2[1] + col2 * r.col2[2] + col3 * r.col2[3];
	col3 = col0 * r.col3[0] + col1 * r.col3[1] + col2 * r.col3[2] + col3 * r.col3[3];
}
vec4d mat4d::operator[](int i) {
	if (i == 0) return col0;
	if (i == 1) return col1;
	if (i == 2) return col2;
	if (i == 3) return col3;
	throw "Index out of range!";
}
mat4d::operator mat4() {
	return { col0, col1, col2, col3 };
}
mat4d createTranslate(vec3d v) {
	mat4d m;
	m.col3.x = v.x;
	m.col3.y = v.y;
	m.col3.z = v.z;
	return m;
}
mat4d createScale(vec3d v) {
	mat4d m;
	m.col0.x = v.x;
	m.col1.y = v.y;
	m.col2.z = v.z;
	return m;
}
mat4d lookAt(vec3d pos, vec3d at, vec3d up) {
	vec3d f(norm(at - pos));
	vec3d s(norm(cross(f, up)));
	vec3d u(cross(s, f));

	mat4d Result;
	Result.col0.x = s.x;
	Result.col1.x = s.y;
	Result.col2.x = s.z;
	Result.col0.y = u.x;
	Result.col1.y = u.y;
	Result.col2.y = u.z;
	Result.col0.z = -f.x;
	Result.col1.z = -f.y;
	Result.col2.z = -f.z;
	Result.col3.x = -dot(s, pos);
	Result.col3.y = -dot(u, pos);
	Result.col3.z = dot(f, pos);
	return Result;
}