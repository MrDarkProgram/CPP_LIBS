#include "main.h"

float ConsoleFPS::t;

void ConsoleFPS::update(float time) {
	if (t >= 1000) {
		std::cout << 1000 / time << " " << time << '\n';
		t = 0;
	}
	t += time;
}
void ConsoleFPS::create() {
	Window::addUpdateEvent(ConsoleFPS::update);
}