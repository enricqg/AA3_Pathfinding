#pragma once
#include "Pathfinding.h"

class GreedyBFS :public Pathfinding
{
public:
	GreedyBFS();
	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);

private:
	Vector2D cell2pix(Vector2D cell);
	float ManhattanDistanceHeuristic(Vector2D n1, Vector2D n2);
};

