#pragma once

// импорт интерфейсных библиотек

#include "../math/math.h"

#ifdef PLANETS_EXPORTS
#define PLANETS_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/planets.lib")
#define PLANETS_API __declspec(dllimport)
#endif

// импорт интерфейса этой библиотеки


// интерфейсные элементы

struct Unit : tetrahedron
{

};

struct Slice : std::vector<Unit>
{
	
};

struct PLANETS_API Planet
{
	std::vector<Slice> slices;
	object obj;

	void Create(unsigned subSph);
};