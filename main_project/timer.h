#pragma once
#include "main.h"

void timerThreadFunction(void(*update)(float), float time) {
	long bank = clock();
	long now = bank;
	long last = bank;
	while (1) {
		now = clock();
		if (now - bank > time) {
			bank += time;
			update((now - last) / 1000.0f);
			last = now;
		}
	}
}
void setTimer(void(*update)(float), float time) {
	std::thread{timerThreadFunction, update, time}.detach();
}