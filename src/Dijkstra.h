#pragma once
#include "Pathfinding.h"

class Dijkstra :public Pathfinding
{
public:
	Dijkstra();
	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);

private:
	Vector2D cell2pix(Vector2D cell);
};

