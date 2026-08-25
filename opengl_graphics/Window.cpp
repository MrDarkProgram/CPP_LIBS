#include "main.h"

GLFWwindow* Window::window;
std::set<void(*)(float)> Window::updateEvent;
std::set<void(*)(float, float)> Window::resizeEvent;
int Window::width;
int Window::height;

void Window::resize(GLFWwindow* window, int width, int height) {
	Window::width = width;
	Window::height = height;
	glViewport(0, 0, width, height);
	for (void(*func)(float, float) : resizeEvent) func(width, height);
}

void Window::create() {
	create(1600, 900, "window");
}
void Window::create(int w, int h, const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	width = w;
	height = h;
	window = glfwCreateWindow(w, h, name, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetWindowSizeCallback(window, resize);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.3, 0.5, 0.7, 1);
}

void Window::run() {
	float time{};
	long last = clock();
	while (!glfwWindowShouldClose(window)) {
		long now = clock();

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time = (time * 15 + now - last) / 16;
		for (void(*func)(float) : updateEvent) func(time);

		glfwSwapBuffers(window);

		//long sleep = clock();
		//Sleep(max(1000.0f / 240 - (sleep - now), 0));
		//Sleep(10); // опять костыль !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		last = now;
	}
}

void Window::close() {
	glfwSetWindowShouldClose((GLFWwindow*)window, 1);
}

void Window::addUpdateEvent(void(*update)(float)) {
	updateEvent.insert(update);
}

void Window::remUpdateEvent(void(*update)(float)) {
	updateEvent.erase(update);
}

void Window::addResizeEvent(void(*resize)(float, float)) {
	resizeEvent.insert(resize);
}

void Window::remResizeEvent(void(*resize)(float, float)) {
	resizeEvent.erase(resize);
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

void Window::enableBlockFaceCulling()
{
	glEnable(GL_CULL_FACE);
}

void Window::disableBlockFaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void Window::setSkyColor(vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
}

void Window::setVSync(int mode)
{
	glfwSwapInterval(mode);
}

GLFWwindow* Window::getWindow() {
	return window;
}