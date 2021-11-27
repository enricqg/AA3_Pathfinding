#pragma once
#include <vector>
#include "Vector2D.h"

struct Path
{
	std::vector<Vector2D> points; //resultat pathfinding
	static const int ARRIVAL_DISTANCE = 35;
};
