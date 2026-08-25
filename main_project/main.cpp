#include "main.h"
#include "graph_tests.h"
#include "atom.h"
#include "timer.h"


/*void __update(HWND, UINT, UINT_PTR, DWORD) {
	updateG(time);
}*/
//#define time 25 / 1000.0f
void main() {
	init();
	basis();
	
	initPhys();
	CreateAtomsCloud({-200, 0, -200}, {200, 0, 200}, 1, 500);
	//MallocAtoms(2); CreateAtom({ -2, 0, 5 }, {0, 0.1f, 0}); CreateAtom({ 2.0f, 0, 5 });

	StartAsyncUpdate(33);

	//createObjectsG({ -200, -20, -200 }, { 200, 20, 200 }, 1, 1, 100);
	//SetTimer(0, 0, time, __update);

	world();
}