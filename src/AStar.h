#pragma once
#include "Pathfinding.h"

class AStar :public Pathfinding
{
public:
	AStar();
	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos);

private:
	Vector2D cell2pix(Vector2D cell); 
	float AStar::ManhattanDistanceHeuristic(Vector2D n1, Vector2D n2);
};

