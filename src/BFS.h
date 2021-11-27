#pragma once
#include "Pathfinding.h"
#include "Node.h"

class BFS:public Pathfinding
{
	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);

};

