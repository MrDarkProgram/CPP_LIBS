#include "main.h"

constexpr signed char triTable[256][16] = {
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
	{3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
	{3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
	{3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
	{9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
	{9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
	{2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
	{8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
	{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
	{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
	{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
	{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
	{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
	{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
	{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
	{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
	{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
	{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
	{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
	{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
	{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
	{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
	{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
	{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
	{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
	{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
	{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
	{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
	{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
	{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
	{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
	{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
	{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
	{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
	{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
	{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
	{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
	{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
	{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
	{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
	{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
	{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
	{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
	{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
	{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
	{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
	{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
	{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
	{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
	{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
	{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
	{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
	{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
	{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
	{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
	{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
	{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
	{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
	{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
	{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
	{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
	{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
	{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
	{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
	{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
	{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
	{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
	{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
	{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
	{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
	{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
	{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
	{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
	{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
	{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
	{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
	{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
	{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
	{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
	{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
	{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
	{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
	{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
	{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
	{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
	{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
	{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
	{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
	{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
	{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
	{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
	{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
	{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
	{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
	{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
	{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
	{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
	{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
	{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
	{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
	{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
	{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
	{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
	{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
	{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
	{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
	{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
	{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
	{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
	{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
	{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
	{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
	{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
	{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
	{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
	{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
	{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
	{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
	{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
	{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
	{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
	{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
	{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
	{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
	{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
	{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
	{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
	{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
	{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
	{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
	{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
	{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
	{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
	{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
	{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
	{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
	{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
	{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
	{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
	{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
	{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
	{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
	{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
	{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
	{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
	{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
	{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
	{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
	{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
	{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
	{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
	{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
	{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
	{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
	{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
	{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
	{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
	{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
	{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
	{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
	{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
	{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
	{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
	{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
	{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
	{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
	{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
	{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

DotCloud::DotCloud()
{
	for (unsigned i = 0; i < cloudSize; i++) {
		for (unsigned j = 0; j < cloudSize; j++) {
			for (unsigned k = 0; k < cloudSize; k++) {
				unsigned x, y, z;
				x = i - cloudSize / 2;
				y = j - cloudSize / 2;
				z = k - cloudSize / 2;
				unsigned r = sqrt(x * x + y * y + z * z);
				unsigned rx = sqrt(y * y + z * z);
				if (r < cloudSize / 3) {
					cloud[i][j][k] = Matter::something;
				}
				else {
					cloud[i][j][k] = Matter::none;
				}
				//cloud[i][j][k] = Matter::something;
			}
		}
	}
}

void DotCloud::setDot(vec3 pos, Matter matter)
{
	cloud[(int)pos.x][(int)pos.y][(int)pos.z] = matter;
}

object DotCloud::generatePointModel() const
{
	object obj{};
	//obj.center = { cloudSize / 2, cloudSize / 2 , cloudSize / 2 };
	obj.mode = points;
	obj.pos = pos;
	obj.rot = rot;
	obj.scl = scl;
	vertexes verts{};
	for (unsigned i = 0; i < cloudSize; i++) {
		for (unsigned j = 0; j < cloudSize; j++) {
			for (unsigned k = 0; k < cloudSize; k++) {
				if (cloud[i][j][k] == Matter::something) {
					for (int i0 = -1; i0 < 2; i0++) {
						if (i + i0 >= 0 && i + i0 < cloudSize) if (cloud[i + i0][j][k] == Matter::none) {
							goto exred;
						}
					}
					for (int j0 = -1; j0 < 2; j0++) {
						if (j + j0 >= 0 && j + j0 < cloudSize) if (cloud[i][j + j0][k] == Matter::none) {
							goto exred;
						}
					}
					for (int k0 = -1; k0 < 2; k0++) {
						if (k + k0 >= 0 && k + k0 < cloudSize) if (cloud[i][j][k + k0] == Matter::none) {
							goto exred;
						}
					}
					verts.push_back({ {(float)i, (float)j, (float)k}, {}, {1, 1, 1, 1}, {}, {} });
					continue;
				exred:
					verts.push_back({ {(float)i, (float)j, (float)k}, {}, {1, 0, 0, 1}, {}, {} });
				}
			}
		}
	}
	obj.vert = verts;
	return obj;
}

object DotCloud::generateLineModel() const
{
	object obj{};
	//obj.center = { cloudSize / 2, cloudSize / 2 , cloudSize / 2 };
	obj.mode = dyn_lines;
	obj.pos = pos;
	obj.rot = rot;
	obj.scl = scl;
	unsigned char sides[cloudSize][cloudSize][cloudSize]{};
	for (unsigned i = 0; i < cloudSize; i++) {
		for (unsigned j = 0; j < cloudSize; j++) {
			for (unsigned k = 0; k < cloudSize; k++) {
				if (cloud[i][j][k] == Matter::something) {
					if (i + 1 < cloudSize && cloud[i + 1][j][k] == Matter::none) sides[i][j][k] |= 0b00000001;
					if (i - 1 >= 0 && cloud[i - 1][j][k] == Matter::none) sides[i][j][k] |= 0b00000010;
					if (j + 1 < cloudSize && cloud[i][j + 1][k] == Matter::none) sides[i][j][k] |= 0b00000100;
					if (j - 1 >= 0 && cloud[i][j - 1][k] == Matter::none) sides[i][j][k] |= 0b00001000;
					if (k + 1 < cloudSize && cloud[i][j][k + 1] == Matter::none) sides[i][j][k] |= 0b00010000;
					if (k - 1 >= 0 && cloud[i][j][k - 1] == Matter::none) sides[i][j][k] |= 0b00100000;
				}
			}
		}
	}
	for (unsigned i = 0; i < cloudSize; i++) {
		for (unsigned j = 0; j < cloudSize; j++) {
			for (unsigned k = 0; k < cloudSize; k++) {
				if (sides[i][j][k] != 0) {
					vec4 color{ 0, 0, 0, 1 };
					if (i == selected.x && j == selected.y && k == selected.z) color = { 1, 1, 1, 1 };
					int ia, ja, ka, ib, jb, kb;
					switch (i)
					{
					case 0:
						ia = 0;
						ib = 2;
						break;
					case cloudSize - 1:
						ia = cloudSize - 3;
						ib = cloudSize - 1;
						break;
					default:
						ia = i - 1;
						ib = i + 2;
						break;
					}
					switch (j)
					{
					case 0:
						ja = 0;
						jb = 2;
						break;
					case cloudSize - 1:
						ja = cloudSize - 3;
						jb = cloudSize - 1;
						break;
					default:
						ja = j - 1;
						jb = j + 2;
						break;
					}
					switch (k)
					{
					case 0:
						ka = 0;
						kb = 2;
						break;
					case cloudSize - 1:
						ka = cloudSize - 3;
						kb = cloudSize - 1;
						break;
					default:
						ka = k - 1;
						kb = k + 2;
						break;
					}
					for (int i1 = ia; i1 < ib; i1++) {
						for (int j1 = ja; j1 < jb; j1++) {
							for (int k1 = ka; k1 < kb; k1++) {
								if (i1 == i && j1 == j && k1 == k) continue;
								if (sides[i1][j1][k1] != 0) {
									obj.vert.push_back({ {(float)i, (float)j, (float)k}, {}, color, {}, {} });
									obj.vert.push_back({ {(float)i1, (float)j1, (float)k1}, {}, color, {}, {} });
								}
							}
						}
					}
				}
			}
		}
	}
	return obj;
}


float getRand(vec3 pos, float seed, float intensity) {
	//pos /= cloudSize;
	double x =
		seed +
		pos.x * 0.991 +
		pos.y * 0.983 +
		pos.z * 0.977;
	double y =
		pos.x * pos.y * 0.971 +
		pos.y * pos.z * 0.967 +
		pos.x * pos.z * 0.953 +
		pos.x * pos.y * pos.z * (0.947 + seed) / 2;
	//unsigned long xx = *(unsigned long*)&x;
	//unsigned long yy = *(unsigned long*)&y;
	//unsigned long zz = xx ^ yy;
	//double z = zz & 1023;
	//z = z / 1023;
	double z = cos(x * y);
	return z * intensity + 0.5f * (1 - intensity);
}

constexpr float OFFSET_INTEN = 1.0f;
constexpr float INTEN = 1.0f;
vec3 getCurrentVert(vec3 _p1, vec3 _p2, vec3 pos) {
	vec3 p1 = _p1;
	vec3 p2 = _p2;
	p1.x += getRand(pos + _p1, 1.009f, OFFSET_INTEN);
	p1.y += getRand(pos + _p1, 1.013f, OFFSET_INTEN);
	p1.z += getRand(pos + _p1, 1.019f, OFFSET_INTEN);
	p2.x += getRand(pos + _p2, 1.009f, OFFSET_INTEN);
	p2.y += getRand(pos + _p2, 1.013f, OFFSET_INTEN);
	p2.z += getRand(pos + _p2, 1.019f, OFFSET_INTEN);
	float v1 = getRand(pos + p1, 0.997f, INTEN);
	float v2 = getRand(pos + p2, 0.997f, INTEN);
	return (p1 * v1 + p2 * v2) * (1.0f / (v1 + v2));
}
vec3 getVert(unsigned edge, vec3 pos) {
	vec3 vert{};
	//float val = 0.5f, val0, val1;
	//float x0, y0, z0, x1, y1, z1;
	switch (edge)
	{
	case 0:
		vert = getCurrentVert({ 0, 0, 0 }, {1, 0, 0}, pos);
		//val0 = getRand(pos + vec3{ 0, 0, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 0, 0 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { val, 0, 0 };
		break;
	case 1:
		vert = getCurrentVert({ 1, 0, 0 }, { 1, 1, 0 }, pos);
		//val0 = getRand(pos + vec3{ 1, 0, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 1, 0 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 1, val, 0 };
		break;
	case 2:
		vert = getCurrentVert({ 0, 1, 0 }, { 1, 1, 0 }, pos);
		//val0 = getRand(pos + vec3{ 0, 1, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 1, 0 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { val, 1, 0 };
		break;
	case 3:
		vert = getCurrentVert({ 0, 0, 0 }, { 0, 1, 0 }, pos);
		//val0 = getRand(pos + vec3{ 0, 0, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 0, 1, 0 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 0, val, 0 };
		break;
	case 4:
		vert = getCurrentVert({ 0, 0, 1 }, { 1, 0, 1 }, pos);
		//val0 = getRand(pos + vec3{ 0, 0, 1 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 0, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { val, 0, 1 };
		break;
	case 5:
		vert = getCurrentVert({ 1, 0, 1 }, { 1, 1, 1 }, pos);
		//val0 = getRand(pos + vec3{ 1, 0, 1 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 1, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 1, val, 1 };
		break;
	case 6:
		vert = getCurrentVert({ 0, 1, 1 }, { 1, 1, 1 }, pos);
		//val0 = getRand(pos + vec3{ 0, 1, 1 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 1, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { val, 1, 1 };
		break;
	case 7:
		vert = getCurrentVert({ 0, 0, 1 }, { 0, 1, 1 }, pos);
		//val0 = getRand(pos + vec3{ 0, 0, 1 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 0, 1, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 0, val, 1 };
		break;
	case 8:
		vert = getCurrentVert({ 0, 0, 0 }, { 0, 0, 1 }, pos);
		//val0 = getRand(pos + vec3{ 0, 0, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 0, 0, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 0, 0, val };
		break;
	case 9:
		vert = getCurrentVert({ 1, 0, 0 }, { 1, 0, 1 }, pos);
		//val0 = getRand(pos + vec3{ 1, 0, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 0, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 1, 0, val };
		break;
	case 10:
		vert = getCurrentVert({ 1, 1, 0 }, { 1, 1, 1 }, pos);
		//val0 = getRand(pos + vec3{ 1, 1, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 1, 1, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 1, 1, val };
		break;
	case 11:
		vert = getCurrentVert({ 0, 1, 0 }, { 0, 1, 1 }, pos);
		//val0 = getRand(pos + vec3{ 0, 1, 0 }, 0.997f, INTEN);
		//val1 = 1 - getRand(pos + vec3{ 0, 1, 1 }, 0.997f, INTEN);
		//if (val0 + val1 != 0) val = val0 / (val0 + val1);
		//vert = { 0, 1, val };
		break;
	}
	return vert;
}

object DotCloud::generatePolygonModel() const
{
	object obj{};
	//obj.center = { cloudSize / 2, cloudSize / 2 , cloudSize / 2 };
	obj.mode = dyn_triangles;
	obj.pos = pos;
	obj.rot = rot;
	obj.scl = scl;
	for (unsigned i = 0; i < cloudSize - 1; i++) {
		for (unsigned j = 0; j < cloudSize - 1; j++) {
			for (unsigned k = 0; k < cloudSize - 1; k++) {
				unsigned char cube{};
				vec4 color1{1, 1, 1, 1};
				if ((i == selected.x || i + 1 == selected.x) &&
					(j == selected.y || j + 1 == selected.y) &&
					(k == selected.z || k + 1 == selected.z)) {
					color1 = { 0.5, 1, 0.5, 1 };
				}
				if (cloud[i][j][k] == Matter::something) cube |= 1;
				if (cloud[i + 1][j][k] == Matter::something) cube |= 2;
				if (cloud[i + 1][j + 1][k] == Matter::something) cube |= 4;
				if (cloud[i][j + 1][k] == Matter::something) cube |= 8;
				if (cloud[i][j][k + 1] == Matter::something) cube |= 16;
				if (cloud[i + 1][j][k + 1] == Matter::something) cube |= 32;
				if (cloud[i + 1][j + 1][k + 1] == Matter::something) cube |= 64;
				if (cloud[i][j + 1][k + 1] == Matter::something) cube |= 128;
				float r = 0.997f;
				for (unsigned o = 0; triTable[cube][o] != -1; o+=3) {
					//vec3 r1 = getRandOffset({(float)i, (float)j, (float)k}, r, 1.0f);
					//vec3 r2 = getRandOffset({(float)i, (float)j, (float)k}, r1.z, 1.0f);
					//vec3 r3 = getRandOffset({(float)i, (float)j, (float)k}, r2.z, 1.0f);
					//r = r3.z;

					vec3 vert1 = getVert(triTable[cube][o], { (float)i, (float)j, (float)k });
					vec3 vert2 = getVert(triTable[cube][o + 1], { (float)i, (float)j, (float)k });
					vec3 vert3 = getVert(triTable[cube][o + 2], { (float)i, (float)j, (float)k });
					vec3 normal = norm(cross(vert1 - vert3, vert1 - vert2));
					obj.vert.push_back({ vert2 + vec3{(float)i, (float)j, (float)k}, normal, color1, {}, i * cloudSize * cloudSize + j * cloudSize + k });
					obj.vert.push_back({ vert1 + vec3{(float)i, (float)j, (float)k}, normal, color1, {}, i * cloudSize * cloudSize + j * cloudSize + k });
					obj.vert.push_back({ vert3 + vec3{(float)i, (float)j, (float)k}, normal, color1, {}, i * cloudSize * cloudSize + j * cloudSize + k });
				}
			}
		}
	}
	return obj;
}

vec3 DotCloud::checkRay(vec3 startPos, vec3 forward, float dist) const
{
	mat4d m = createScale(vec3{ 1 / scl.x, 1 / scl.y, 1 / scl.z }) * createRotation(inverse(rot)) * createTranslate(vec3d{ -pos.x, -pos.y, -pos.z });
	startPos = m * startPos;
	forward = m * (forward * dist);
	dist = forward.length();
	forward.norm();
	
	float dX = forward.x, dY = forward.y, dZ = forward.z;
	int sX = dX > 0 ? 1 : dX < 0 ? -1 : 0, sY = dY > 0 ? 1 : dY < 0 ? -1 : 0, sZ = dZ > 0 ? 1 : dZ < 0 ? -1 : 0;
	float tdX, tdY, tdZ;
	float tmX, tmY, tmZ;

	if (sX != 0) {
		tdX = 1 / abs(dX);
		if (sX == 1) {
			tmX = ((int)startPos.x - startPos.x) / dX;
		}
		else {
			tmX = ((int)startPos.x - 1 - startPos.x) / dX;
		}
	}
	else {
		tdX = INFINITY;
		tmX = INFINITY;
	}

	if (sY != 0) {
		tdY = 1 / abs(dY);
		if (sY == 1) {
			tmY = ((int)startPos.y - startPos.y) / dY;
		}
		else {
			tmY = ((int)startPos.y - 1 - startPos.y) / dY;
		}
	}
	else {
		tdY = INFINITY;
		tmY = INFINITY;
	}

	if (sZ != 0) {
		tdZ = 1 / abs(dZ);
		if (sZ == 1) {
			tmZ = ((int)startPos.z - startPos.z) / dZ;
		}
		else {
			tmZ = ((int)startPos.z - 1 - startPos.z) / dZ;
		}
	}
	else {
		tdZ = INFINITY;
		tmZ = INFINITY;
	}

	int x = startPos.x, y = startPos.y, z = startPos.z;
	int ex = x + forward.x * dist, ey = y + forward.y * dist, ez = z + forward.z * dist;

	//std::cout << "==================" << '\n';
	//std::cout << vec3((float)ex, (float)ey, (float)ez) << '\n';
	//std::cout << vec3((float)x, (float)y, (float)z) << '\n';

	if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
		if (cloud[x][y][z] == Matter::something) return vec3{ (float)x, (float)y, (float)z };
	}
	while (/*x != ex || y != ey || z != ez*/(vec3{(float)x, (float)y, (float)z} - startPos).length() < dist) {
		if (tmX < tmY && tmX < tmZ) {
			x += sX;
			tmX += tdX;
		}
		else if (tmY < tmZ) {
			y += sY;
			tmY += tdY;
		}
		else {
			z += sZ;
			tmZ += tdZ;
		}
		//std::cout << vec3((float)x, (float)y, (float)z) << ' ';
		if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
			if (cloud[x][y][z] == Matter::something) return vec3{ (float)x, (float)y, (float)z };
		}
	}

	//std::cout << '\n';

	return {-1, -1, -1};
}

void DotCloud::checkRay(vec3 startPos, vec3 forward, float dist, vec3& obj, vec3& preObj) const
{
	mat4d m = createScale(vec3{ 1 / scl.x, 1 / scl.y, 1 / scl.z }) * createRotation(inverse(rot)) * createTranslate(vec3d{ -pos.x, -pos.y, -pos.z });
	startPos = m * startPos;
	forward = m * (forward * dist);
	dist = forward.length();
	forward.norm();

	float dX = forward.x, dY = forward.y, dZ = forward.z;
	int sX = dX > 0 ? 1 : dX < 0 ? -1 : 0, sY = dY > 0 ? 1 : dY < 0 ? -1 : 0, sZ = dZ > 0 ? 1 : dZ < 0 ? -1 : 0;
	float tdX, tdY, tdZ;
	float tmX, tmY, tmZ;

	if (sX != 0) {
		tdX = 1 / abs(dX);
		if (sX == 1) {
			tmX = ((int)startPos.x - startPos.x) / dX;
		}
		else {
			tmX = ((int)startPos.x - 1 - startPos.x) / dX;
		}
	}
	else {
		tdX = INFINITY;
		tmX = INFINITY;
	}

	if (sY != 0) {
		tdY = 1 / abs(dY);
		if (sY == 1) {
			tmY = ((int)startPos.y - startPos.y) / dY;
		}
		else {
			tmY = ((int)startPos.y - 1 - startPos.y) / dY;
		}
	}
	else {
		tdY = INFINITY;
		tmY = INFINITY;
	}

	if (sZ != 0) {
		tdZ = 1 / abs(dZ);
		if (sZ == 1) {
			tmZ = ((int)startPos.z - startPos.z) / dZ;
		}
		else {
			tmZ = ((int)startPos.z - 1 - startPos.z) / dZ;
		}
	}
	else {
		tdZ = INFINITY;
		tmZ = INFINITY;
	}

	int x = startPos.x, y = startPos.y, z = startPos.z;
	int ex = x + forward.x * dist, ey = y + forward.y * dist, ez = z + forward.z * dist;

	//std::cout << "==================" << '\n';
	//std::cout << vec3((float)ex, (float)ey, (float)ez) << '\n';
	//std::cout << vec3((float)x, (float)y, (float)z) << '\n';

	if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
		if (cloud[x][y][z] == Matter::something) {
			obj = { (float)x, (float)y, (float)z };
			preObj = { -1, -1, -1 };
			return;
		}
	}
	while (/*x != ex || y != ey || z != ez*/(vec3{ (float)x, (float)y, (float)z } - startPos).length() < dist) {
		if (tmX < tmY && tmX < tmZ) {
			x += sX;
			tmX += tdX;
		}
		else if (tmY < tmZ) {
			y += sY;
			tmY += tdY;
		}
		else {
			z += sZ;
			tmZ += tdZ;
		}
		//std::cout << vec3((float)x, (float)y, (float)z) << ' ';
		if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
			if (cloud[x][y][z] == Matter::something) {
				obj = { (float)x, (float)y, (float)z };
				return;
			}
			preObj = { (float)x, (float)y, (float)z };
		}
	}

	//std::cout << '\n';
}

vec3 DotCloud::checkRayPre(vec3 startPos, vec3 forward, float dist) const
{
	mat4d m = createScale(vec3{ 1 / scl.x, 1 / scl.y, 1 / scl.z }) * createRotation(inverse(rot)) * createTranslate(vec3d{ -pos.x, -pos.y, -pos.z });
	startPos = m * startPos;
	forward = m * (forward * dist);
	dist = forward.length();
	forward.norm();

	float dX = forward.x, dY = forward.y, dZ = forward.z;
	int sX = dX > 0 ? 1 : dX < 0 ? -1 : 0, sY = dY > 0 ? 1 : dY < 0 ? -1 : 0, sZ = dZ > 0 ? 1 : dZ < 0 ? -1 : 0;
	float tdX, tdY, tdZ;
	float tmX, tmY, tmZ;

	if (sX != 0) {
		tdX = 1 / abs(dX);
		if (sX == 1) {
			tmX = ((int)startPos.x - startPos.x) / dX;
		}
		else {
			tmX = ((int)startPos.x - 1 - startPos.x) / dX;
		}
	}
	else {
		tdX = INFINITY;
		tmX = INFINITY;
	}

	if (sY != 0) {
		tdY = 1 / abs(dY);
		if (sY == 1) {
			tmY = ((int)startPos.y - startPos.y) / dY;
		}
		else {
			tmY = ((int)startPos.y - 1 - startPos.y) / dY;
		}
	}
	else {
		tdY = INFINITY;
		tmY = INFINITY;
	}

	if (sZ != 0) {
		tdZ = 1 / abs(dZ);
		if (sZ == 1) {
			tmZ = ((int)startPos.z - startPos.z) / dZ;
		}
		else {
			tmZ = ((int)startPos.z - 1 - startPos.z) / dZ;
		}
	}
	else {
		tdZ = INFINITY;
		tmZ = INFINITY;
	}

	int x = startPos.x, y = startPos.y, z = startPos.z;
	int ex = x + forward.x * dist, ey = y + forward.y * dist, ez = z + forward.z * dist;

	//std::cout << "==================" << '\n';
	//std::cout << vec3((float)ex, (float)ey, (float)ez) << '\n';
	//std::cout << vec3((float)x, (float)y, (float)z) << '\n';

	//if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
	//	if (cloud[x][y][z] == Matter::something) return vec3{ (float)x, (float)y, (float)z };
	//}
	vec3 v{-1, -1, -1};
	while (/*x != ex || y != ey || z != ez*/(vec3{ (float)x, (float)y, (float)z } - startPos).length() < dist) {
		if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
			v = { (float)x, (float)y, (float)z };
		}
		if (tmX < tmY && tmX < tmZ) {
			x += sX;
			tmX += tdX;
		}
		else if (tmY < tmZ) {
			y += sY;
			tmY += tdY;
		}
		else {
			z += sZ;
			tmZ += tdZ;
		}
		//std::cout << vec3((float)x, (float)y, (float)z) << ' ';
		if (x >= 0 && x < cloudSize && y >= 0 && y < cloudSize && z >= 0 && z < cloudSize) {
			if (cloud[x][y][z] == Matter::something) return v;
		}
	}

	//std::cout << '\n';

	return { -1, -1, -1 };
}

vec3 DotCloud::getSelect()
{
	return selected;
}

void DotCloud::setSelect(vec3 select)
{
	selected = select;
}
