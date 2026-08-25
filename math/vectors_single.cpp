#include "main.h"

vec2::vec2() {
	x = y = 0;
}
vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}
vec2 vec2::operator+(vec2 r) {
	return {x + r.x, y + r.y};
}
vec2 vec2::operator-(vec2 r) {
	return { x - r.x, y - r.y };
}
vec2 vec2::operator+() {
	return *this;
}
vec2 vec2::operator-() {
	return { -x, -y};
}
vec2 vec2::operator*(vec2 r) {
	return { x * r.x, y * r.y };
}
vec2 vec2::operator*(float r) {
	return { x * r, y * r };
}
vec2 vec2::operator/(vec2 r) {
	return { x / r.x, y / r.y };
}
vec2 vec2::operator/(float r) {
	return { x / r, y / r };
}
bool vec2::operator==(vec2 r) {
	return x == r.x && y == r.y;
}
bool vec2::operator!=(vec2 r) {
	return x != r.x && y != r.y;
}
void vec2::operator+=(vec2 r) {
	x = x + r.x;
	y = y + r.y;
}
void vec2::operator-=(vec2 r) {
	x = x - r.x;
	y = y - r.y;
}
void vec2::operator*=(vec2 r) {
	x = x * r.x;
	y = y * r.y;
}
void vec2::operator*=(float r) {
	x = x * r;
	y = y * r;
}
void vec2::operator/=(vec2 r) {
	x = x / r.x;
	y = y / r.y;
}
void vec2::operator/=(float r) {
	x = x / r;
	y = y / r;
}
float vec2::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	throw "Index out of range!";
}
float vec2::length() {
	return sqrtf(x * x + y * y);
}
float vec2::length_squared() {
	return x * x + y * y;
}
std::ostream& operator<<(std::ostream& out, vec2 a) {
	out << '{' << a.x << ", " << a.y << '}';
	return out;
}
float dot(vec2 a, vec2 b) {
	return a.x * b.x + a.y * b.y;
}
void vec2::norm() {
	float l = length();
	x /= l;
	y /= l;
}
vec2 norm(vec2 v) {
	float l = v.length();
	return { v.x / l, v.y / l };
}
vec2::operator vec2d() {
	return { (double)x, (double)y };
}

vec3::vec3() {
	x = y = z = 0;
}
vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
vec3::vec3(vec2 xy, float z) {
	x = xy.x;
	y = xy.y;
	this->z = z;
}
vec3 vec3::operator+(vec3 r) {
	return { x + r.x, y + r.y, z + r.z };
}
vec3 vec3::operator-(vec3 r) {
	return { x - r.x, y - r.y, z - r.z };
}
vec3 vec3::operator+() {
	return *this;
}
vec3 vec3::operator-() {
	return { -x, -y, -z };
}
vec3 vec3::operator*(vec3 r) {
	return { x * r.x, y * r.y, z * r.z };
}
vec3 vec3::operator*(float r) {
	return { x * r, y * r, z * r };
}
vec3 vec3::operator/(vec3 r) {
	return { x / r.x, y / r.y, z / r.z };
}
vec3 vec3::operator/(float r) {
	return { x / r, y / r, z / r };
}
bool vec3::operator==(vec3 r) {
	return x == r.x && y == r.y && z == r.z;
}
bool vec3::operator!=(vec3 r) {
	return x != r.x && y != r.y && z != r.z;
}
void vec3::operator+=(vec3 r) {
	x = x + r.x;
	y = y + r.y;
	z = z + r.z;
}
void vec3::operator-=(vec3 r) {
	x = x - r.x;
	y = y - r.y;
	z = z - r.z;
}
void vec3::operator*=(vec3 r) {
	x = x * r.x;
	y = y * r.y;
	z = z * r.z;
}
void vec3::operator*=(float r) {
	x = x * r;
	y = y * r;
	z = z * r;
}
void vec3::operator/=(vec3 r) {
	x = x / r.x;
	y = y / r.y;
	z = z / r.z;
}
void vec3::operator/=(float r) {
	x = x / r;
	y = y / r;
	z = z / r;
}
float vec3::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	throw "Index out of range!";
}
float vec3::length() {
	return sqrtf(x * x + y * y + z * z);
}
float vec3::length_squared() {
	return x * x + y * y + z * z;
}
std::ostream& operator<<(std::ostream& out, vec3 a) {
	out << '{' << a.x << ", " << a.y << ", " << a.z << '}';
	return out;
}
float dot(vec3 a, vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
vec3 cross(vec3 a, vec3 b) {
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
float triple(vec3 a, vec3 b, vec3 c) {
	return a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y - a.z * b.y * c.x - a.y * b.x * c.z - a.x * b.z * c.y;
}
void vec3::norm() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}
vec3 norm(vec3 v) {
	float l = v.length();
	return { v.x / l, v.y / l, v.z / l };
}
vec3::operator vec3d() {
	return { (double)x, (double)y, (double)z };
}

vec4::vec4() {
	x = y = z = w = 0;
}
vec4::vec4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
vec4::vec4(vec2 xy, float z, float w) {
	x = xy.x;
	y = xy.y;
	this->z = z;
	this->w = w;
}
vec4::vec4(vec3 xyz, float w) {
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	this->w = w;
}
vec4 vec4::operator+(vec4 r) {
	return { x + r.x, y + r.y, z + r.z, w + r.w };
}
vec4 vec4::operator-(vec4 r) {
	return { x - r.x, y - r.y, z - r.z, w - r.w };
}
vec4 vec4::operator+() {
	return *this;
}
vec4 vec4::operator-() {
	return { -x, -y, -z, -w };
}
vec4 vec4::operator*(vec4 r) {
	return { x * r.x, y * r.y, z * r.z, w * r.w };
}
vec4 vec4::operator*(float r) {
	return { x * r, y * r, z * r, w * r };
}
vec4 vec4::operator/(vec4 r) {
	return { x / r.x, y / r.y, z / r.z, w / r.w };
}
vec4 vec4::operator/(float r) {
	return { x / r, y / r, z / r, w / r };
}
bool vec4::operator==(vec4 r) {
	return x == r.x && y == r.y && z == r.z && w == r.w;
}
bool vec4::operator!=(vec4 r) {
	return x != r.x && y != r.y && z != r.z && w != r.w;
}
void vec4::operator+=(vec4 r) {
	x = x + r.x;
	y = y + r.y;
	z = z + r.z;
	w = w + r.w;
}
void vec4::operator-=(vec4 r) {
	x = x - r.x;
	y = y - r.y;
	z = z - r.z;
	w = w - r.w;
}
void vec4::operator*=(vec4 r) {
	x = x * r.x;
	y = y * r.y;
	z = z * r.z;
	w = w * r.w;
}
void vec4::operator*=(float r) {
	x = x * r;
	y = y * r;
	z = z * r;
	w = w * r;
}
void vec4::operator/=(vec4 r) {
	x = x / r.x;
	y = y / r.y;
	z = z / r.z;
	w = w / r.w;
}
void vec4::operator/=(float r) {
	x = x / r;
	y = y / r;
	z = z / r;
	w = w / r;
}
float vec4::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	if (i == 3) return w;
	throw "Index out of range!";
}
float vec4::length() {
	return sqrtf(x * x + y * y + z * z + w * w);
}
float vec4::length_squared() {
	return x * x + y * y + z * z + w * w;
}
std::ostream& operator<<(std::ostream& out, vec4 a) {
	out << '{' << a.x << ", " << a.y << ", " << a.z << ", " << a.w << '}';
	return out;
}
float dot(vec4 a, vec4 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
void vec4::norm() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}
vec4 norm(vec4 v) {
	float l = v.length();
	return { v.x / l, v.y / l, v.z / l, v.w / l };
}
vec4::operator vec4d() {
	return { (double)x, (double)y, (double)z, (double)w };
}