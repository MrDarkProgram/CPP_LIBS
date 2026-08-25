#include "main.h"

quaternion::quaternion() {
	w = 1;
	x = y = z = 0;
}
quaternion::quaternion(float x, float y, float z, float w) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}
quaternion::quaternion(vec3 angles) {
	float cx = cos(angles.x * 0.5);
	float sx = sin(angles.x * 0.5);
	float cy = cos(angles.y * 0.5);
	float sy = sin(angles.y * 0.5);
	float cz = cos(angles.z * 0.5);
	float sz = sin(angles.z * 0.5);
	w = cx * cy * cz + sx * sy * sz;
	x = sx * cy * cz - cx * sy * sz;
	y = cx * sy * cz + sx * cy * sz;
	z = cx * cy * sz - sx * sy * cz;
}
quaternion::quaternion(vec3 axis, float angle) {
	w = cos(angle / 2);
	x = axis.x * sin(angle / 2);
	y = axis.y * sin(angle / 2);
	z = axis.z * sin(angle / 2);
}
vec3 quaternion::toEulerAngles() {
	vec3 angles{};

	float sinr_cosp = 2 * (w * x + y * z);
	float cosr_cosp = 1 - 2 * (x * x + y * y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	float sinp = std::sqrt(1 + 2 * (w * y - x * z));
	float cosp = std::sqrt(1 - 2 * (w * y - x * z));
	angles.y = 2 * std::atan2(sinp, cosp) - PI / 2;

	float siny_cosp = 2 * (w * z + x * y);
	float cosy_cosp = 1 - 2 * (y * y + z * z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);
	return angles;
}
vec4 quaternion::toAxisAngle() {
	throw "not released!";
}
quaternion quaternion::operator*(quaternion r) {
	quaternion q{};
	q.w = w * r.w - x * r.x - y * r.y - z * r.z;
	q.x = w * r.x + x * r.w + y * r.z - z * r.y;
	q.y = w * r.y - x * r.z + y * r.w + z * r.x;
	q.z = w * r.z + x * r.y - y * r.x + z * r.w;
	return q;
}
bool quaternion::operator==(quaternion r) {
	return w == r.w && x == r.x && y == r.y && z == r.z;
}
bool quaternion::operator!=(quaternion r) {
	return w != r.w && x != r.x && y != r.y && z != r.z;
}
void quaternion::operator*=(quaternion r) {
	w = w * r.w - x * r.x - y * r.y - z * r.z;
	x = w * r.x + x * r.w + y * r.z - z * r.y;
	y = w * r.y - x * r.z + y * r.w + z * r.x;
	z = w * r.z + x * r.y - y * r.x + z * r.w;
}
float quaternion::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	if (i == 3) return w;
	throw "Index out of range!";
}
float quaternion::length() {
	return sqrtf(x * x + y * y + z * z + w * w);
}
float quaternion::length_squared() {
	return w * w + x * x + y * y + z * z;
}
quaternion quaternion::norm() {
	quaternion q = *this;
	float l = length();
	q.w /= l;
	q.x /= l;
	q.y /= l;
	q.z /= l;
	return q;
}
void quaternion::norm_this() {
	float l = length();
	w /= l;
	x /= l;
	y /= l;
	z /= l;
}

quaternion fromEulerAngles(vec3 angles) {
	float cx = cos(angles.x * 0.5);
	float sx = sin(angles.x * 0.5);
	float cy = cos(angles.y * 0.5);
	float sy = sin(angles.y * 0.5);
	float cz = cos(angles.z * 0.5);
	float sz = sin(angles.z * 0.5);
	quaternion q;
	q.w = cx * cy * cz + sx * sy * sz;
	q.x = sx * cy * cz - cx * sy * sz;
	q.y = cx * sy * cz + sx * cy * sz;
	q.z = cx * cy * sz - sx * sy * cz;
	return q;
}
quaternion fromAxisAngle(vec3 axis, float angle) {
	return
	{ axis.x * sin(angle / 2),
	  axis.y * sin(angle / 2),
	  axis.z * sin(angle / 2),
	  cos(angle / 2) };
}

MATH_API quaternion inverse(quaternion q)
{
	float n = q.length_squared();
	return { -q.x / n, -q.y / n, -q.z / n, q.w / n };
}

MATH_API std::ostream& operator<<(std::ostream& out, quaternion a)
{
	out << "{(" << a.x << ", " << a.y << ", " << a.z << "), " << a.w << '}';
	return out;
}
