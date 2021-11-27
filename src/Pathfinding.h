#pragma once
#include <vector>
#include "Vector2D.h"
class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	virtual std::vector<Vector2D> CalculatePath(Vector2D initialPos, Vector2D targetPos);
};

