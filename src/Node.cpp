#include "Node.h"

Node::Node(int _x, int _y, int _weight) : weight(_weight)
{
	pos.x = _x;
	pos.y = _y;
}

void Node::SetPosition(int _x, int _y)
{
	pos.x = _x;
	pos.y = _y;
}

void Node::SetWeight(int _weight)
{
	weight = _weight;
}

void Node::AddNeighbour(Node* neighbour)
{
	neighbours.push_back(neighbour);
}

int Node::GetWeight()
{
	return weight;
}
