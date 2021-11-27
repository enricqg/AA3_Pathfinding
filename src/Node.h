#pragma once
#include <vector>
#include "utils.h"
#include "Vector2D.h"

class Node
{
public:
	Node(int _x, int _y, int _weight);

private:
	Vector2D pos;
	std::vector<Node*> neighbours;
	int weight;

public:

	void SetPosition(int _x, int _y);
	void SetWeight(int _weight);
	void AddNeighbour(Node* neighbour);
	int GetWeight();
	

};

