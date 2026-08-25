#include "main.h"

mat4 Camera::getView() {
	//return perspective(1.57f, (float)Window::getWidth() / Window::getHeight(), 0.1f, 1000.0f) * lookAt({}, forward, up);
	return perspective(fov, (float)Window::getWidth() / Window::getHeight(), nearFront, farFront) * lookAt((vec3)pos, forward + pos, up);
}

vec3d Camera::getPos() {
	return pos;
}

vec3 Camera::getForward() {
	return forward;
}

vec3 Camera::getUp() {
	return up;
}

float Camera::getFov()
{
	return fov;
}

float Camera::getFarFront()
{
	return farFront;
}

float Camera::getNearFront()
{
	return nearFront;
}

void Camera::setPos(vec3d pos) {
	this->pos = pos;
}

void Camera::setForward(vec3 forward) {
	this->forward = forward;
}

void Camera::setUp(vec3 up) {
	this->up = up;
}

void Camera::setFov(float f)
{
	fov = f;
}

void Camera::setFarFront(float f)
{
	farFront = f;
}

void Camera::setNearFront(float f)
{
	nearFront = f;
}
