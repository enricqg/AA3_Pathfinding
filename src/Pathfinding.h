#pragma once
#include <vector>
#include "Vector2D.h"
#include "Node.h"
class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	virtual std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);
	virtual std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos, Node* enemyPos);
};

