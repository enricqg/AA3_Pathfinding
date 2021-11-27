#pragma once
#include "Pathfinding.h"

class BFS:public Pathfinding
{
public:
	BFS();
	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);

private:
	Vector2D cell2pix(Vector2D cell);
};

