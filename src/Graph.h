#pragma once
#include "Node.h"
#include "Grid.h"
#include <vector>

class Graph
{
public:
	Graph();
	Graph(char* filename);

private:
	std::vector<Node*> nodes;
	std::vector< std::vector<int> > ReadFile(char* filename);

public:


};

