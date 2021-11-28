#pragma once
#include "Pathfinding.h"

class AStarVersus :public Pathfinding
{
public:
	AStarVersus();

	std::vector<Vector2D> CalculatePath(Node* initialPos, Node* targetPos, Node* enemyPos);

private:
	Vector2D cell2pix(Vector2D cell);
	float AStarVersus::ManhattanDistanceHeuristic(Vector2D n1, Vector2D n2);
};

