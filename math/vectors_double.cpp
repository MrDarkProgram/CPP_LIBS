#include "main.h"

vec2d::vec2d() {
	x = y = 0;
}
vec2d::vec2d(double x, double y) {
	this->x = x;
	this->y = y;
}
vec2d vec2d::operator+(vec2d r) {
	return { x + r.x, y + r.y };
}
vec2d vec2d::operator-(vec2d r) {
	return { x - r.x, y - r.y };
}
vec2d vec2d::operator+() {
	return *this;
}
vec2d vec2d::operator-() {
	return { -x, -y };
}
vec2d vec2d::operator*(vec2d r) {
	return { x * r.x, y * r.y };
}
vec2d vec2d::operator*(double r) {
	return { x * r, y * r };
}
vec2d vec2d::operator/(vec2d r) {
	return { x / r.x, y / r.y };
}
vec2d vec2d::operator/(double r) {
	return { x / r, y / r };
}
bool vec2d::operator==(vec2d r) {
	return x == r.x && y == r.y;
}
bool vec2d::operator!=(vec2d r) {
	return x != r.x && y != r.y;
}
void vec2d::operator+=(vec2d r) {
	x = x + r.x;
	y = y + r.y;
}
void vec2d::operator-=(vec2d r) {
	x = x - r.x;
	y = y - r.y;
}
void vec2d::operator*=(vec2d r) {
	x = x * r.x;
	y = y * r.y;
}
void vec2d::operator*=(double r) {
	x = x * r;
	y = y * r;
}
void vec2d::operator/=(vec2d r) {
	x = x / r.x;
	y = y / r.y;
}
void vec2d::operator/=(double r) {
	x = x / r;
	y = y / r;
}
double vec2d::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	throw "Index out of range!";
}
double vec2d::length() {
	return sqrt(x * x + y * y);
}
double vec2d::length_squared() {
	return x * x + y * y;
}
std::ostream& operator<<(std::ostream& out, vec2d a) {
	out << '{' << a.x << ", " << a.y << '}';
	return out;
}
double dot(vec2d a, vec2d b) {
	return a.x * b.x + a.y * b.y;
}
void vec2d::norm() {
	double l = length();
	x /= l;
	y /= l;
}
vec2d norm(vec2d v) {
	double l = v.length();
	return { v.x / l, v.y / l };
}
vec2d::operator vec2() {
	return { (float)x, (float)y };
}

vec3d::vec3d() {
	x = y = z = 0;
}
vec3d::vec3d(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
vec3d::vec3d(vec2d xy, double z) {
	x = xy.x;
	y = xy.y;
	this->z = z;
}
vec3d vec3d::operator+(vec3d r) {
	return { x + r.x, y + r.y, z + r.z };
}
vec3d vec3d::operator-(vec3d r) {
	return { x - r.x, y - r.y, z - r.z };
}
vec3d vec3d::operator+() {
	return *this;
}
vec3d vec3d::operator-() {
	return { -x, -y, -z };
}
vec3d vec3d::operator*(vec3d r) {
	return { x * r.x, y * r.y, z * r.z };
}
vec3d vec3d::operator*(double r) {
	return { x * r, y * r, z * r };
}
vec3d vec3d::operator/(vec3d r) {
	return { x / r.x, y / r.y, z / r.z };
}
vec3d vec3d::operator/(double r) {
	return { x / r, y / r, z / r };
}
bool vec3d::operator==(vec3d r) {
	return x == r.x && y == r.y && z == r.z;
}
bool vec3d::operator!=(vec3d r) {
	return x != r.x && y != r.y && z != r.z;
}
void vec3d::operator+=(vec3d r) {
	x = x + r.x;
	y = y + r.y;
	z = z + r.z;
}
void vec3d::operator-=(vec3d r) {
	x = x - r.x;
	y = y - r.y;
	z = z - r.z;
}
void vec3d::operator*=(vec3d r) {
	x = x * r.x;
	y = y * r.y;
	z = z * r.z;
}
void vec3d::operator*=(double r) {
	x = x * r;
	y = y * r;
	z = z * r;
}
void vec3d::operator/=(vec3d r) {
	x = x / r.x;
	y = y / r.y;
	z = z / r.z;
}
void vec3d::operator/=(double r) {
	x = x / r;
	y = y / r;
	z = z / r;
}
double vec3d::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	throw "Index out of range!";
}
double vec3d::length() {
	return sqrt(x * x + y * y + z * z);
}
double vec3d::length_squared() {
	return x * x + y * y + z * z;
}
std::ostream& operator<<(std::ostream& out, vec3d a) {
	out << '{' << a.x << ", " << a.y << ", " << a.z << '}';
	return out;
}
double dot(vec3d a, vec3d b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
vec3d cross(vec3d a, vec3d b) {
	return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
double triple(vec3d a, vec3d b, vec3d c) {
	return a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y - a.z * b.y * c.x - a.y * b.x * c.z - a.x * b.z * c.y;
}
void vec3d::norm() {
	double l = length();
	x /= l;
	y /= l;
	z /= l;
}
vec3d norm(vec3d v) {
	double l = v.length();
	return { v.x / l, v.y / l, v.z / l };
}
vec3d::operator vec3() {
	return { (float)x, (float)y, (float)z };
}

vec4d::vec4d() {
	x = y = z = w = 0;
}
vec4d::vec4d(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
vec4d::vec4d(vec2d xy, double z, double w) {
	x = xy.x;
	y = xy.y;
	this->z = z;
	this->w = w;
}
vec4d::vec4d(vec3d xyz, double w) {
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	this->w = w;
}
vec4d vec4d::operator+(vec4d r) {
	return { x + r.x, y + r.y, z + r.z, w + r.w };
}
vec4d vec4d::operator-(vec4d r) {
	return { x - r.x, y - r.y, z - r.z, w - r.w };
}
vec4d vec4d::operator+() {
	return *this;
}
vec4d vec4d::operator-() {
	return { -x, -y, -z, -w };
}
vec4d vec4d::operator*(vec4d r) {
	return { x * r.x, y * r.y, z * r.z, w * r.w };
}
vec4d vec4d::operator*(double r) {
	return { x * r, y * r, z * r, w * r };
}
vec4d vec4d::operator/(vec4d r) {
	return { x / r.x, y / r.y, z / r.z, w / r.w };
}
vec4d vec4d::operator/(double r) {
	return { x / r, y / r, z / r, w / r };
}
bool vec4d::operator==(vec4d r) {
	return x == r.x && y == r.y && z == r.z && w == r.w;
}
bool vec4d::operator!=(vec4d r) {
	return x != r.x && y != r.y && z != r.z && w != r.w;
}
void vec4d::operator+=(vec4d r) {
	x = x + r.x;
	y = y + r.y;
	z = z + r.z;
	w = w + r.w;
}
void vec4d::operator-=(vec4d r) {
	x = x - r.x;
	y = y - r.y;
	z = z - r.z;
	w = w - r.w;
}
void vec4d::operator*=(vec4d r) {
	x = x * r.x;
	y = y * r.y;
	z = z * r.z;
	w = w * r.w;
}
void vec4d::operator*=(double r) {
	x = x * r;
	y = y * r;
	z = z * r;
	w = w * r;
}
void vec4d::operator/=(vec4d r) {
	x = x / r.x;
	y = y / r.y;
	z = z / r.z;
	w = w / r.w;
}
void vec4d::operator/=(double r) {
	x = x / r;
	y = y / r;
	z = z / r;
	w = w / r;
}
double vec4d::operator[](int i) {
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	if (i == 3) return w;
	throw "Index out of range!";
}
double vec4d::length() {
	return sqrt(x * x + y * y + z * z + w * w);
}
double vec4d::length_squared() {
	return x * x + y * y + z * z + w * w;
}
std::ostream& operator<<(std::ostream& out, vec4d a) {
	out << '{' << a.x << ", " << a.y << ", " << a.z << ", " << a.w << '}';
	return out;
}
double dot(vec4d a, vec4d b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
void vec4d::norm() {
	double l = length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}
vec4d norm(vec4d v) {
	double l = v.length();
	return { v.x / l, v.y / l, v.z / l, v.w / l };
}
vec4d::operator vec4() {
	return { (float)x, (float)y, (float)z, (float)w };
}