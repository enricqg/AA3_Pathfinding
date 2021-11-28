#include "Graph.h"


Graph::Graph()
{
}

Graph::Graph(char* filename)
{
	std::vector< std::vector<int> > tmp_terrain = ReadFile(filename);
	std::vector<std::vector<Node*>> tmp_nodes;

	for (int i = 0; i < tmp_terrain.size(); i++) //ens saltem els contorns
	{
		std::vector<Node*> tmp_nodes_row;
		for (int j = 0; j < tmp_terrain[i].size(); j++)
		{

			Node* tmp_n = new Node(j, i, tmp_terrain[i][j]);
			tmp_nodes_row.push_back(tmp_n); // push a la fila i
		}
		tmp_nodes.push_back(tmp_nodes_row);
	}

	for (int i = 0; i < tmp_nodes.size(); i++) //ens saltem els contorns
	{
		for (int j = 0; j < tmp_nodes[i].size(); j++)
		{
			if (tmp_nodes[i][j]->GetWeight() != 0) // si es mur no llegim
			{

				//mirem els 8 neighbours
				for (int x = -1; x < 2; x++)
				{
					for (int y = -1; y < 2; y++)
					{
						if (y != 0 || x != 0) //si es ell mateix, no es s'afegeix a neighbours
						{
							if (tmp_nodes[i + x][j + y]->GetWeight() != 0) tmp_nodes[i][j]->AddNeighbour(tmp_nodes[i + x][j + y]);
						}
					}
				}

				nodes.push_back(tmp_nodes[i][j]);
			}
		}
	}

	if (true) {}
}

std::vector< std::vector<int> > Graph::ReadFile(char* filename)
{
	std::vector< std::vector<int> > tmp_terrain;
	int num_cell_x = SRC_WIDTH / CELL_SIZE;
	int num_cell_y = SRC_HEIGHT / CELL_SIZE;

	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line))
	{
		std::vector<int> terrain_row;
		std::stringstream lineStream(line);
		std::string cell;
		while (std::getline(lineStream, cell, ','))
			terrain_row.push_back(atoi(cell.c_str()));
		SDL_assert(terrain_row.size() == num_cell_x);
		tmp_terrain.push_back(terrain_row);
	}
	SDL_assert(tmp_terrain.size() == num_cell_y);
	infile.close();

	return tmp_terrain;
}

Node* Graph::cell2node(Vector2D position)
{
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->GetPosition() == position) {
			return nodes[i];
		}
	}

	return nullptr;
}

Vector2D Graph::getNearestExistingPos(Vector2D position)
{
	Node* n = cell2node(position);

	if (n != nullptr) return n->GetPosition();
	
	std::pair<Node*, float> nodeDistance;

	//int x = -1;
	//int y = -1;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; i < 2; i++) {

			if (i == -1 && j == -1) {
				nodeDistance = std::make_pair(cell2node(Vector2D(position.x + i, position.y + j)), Vector2D::Distance(Vector2D(position.x + i, position.y + j), position));
				/*if (nodeDistance.first == nullptr) 
				{ 

					continue; 
				}*/
			}
			else {
				if (cell2node(Vector2D(position.x + i, position.y + j)) == nullptr || (i==0&&j==0))continue;

				else if (nodeDistance.second > Vector2D::Distance(Vector2D(position.x + i, position.y + j), position)) {
					n = nodeDistance.first;
				}
			}
		}
	}

	return n->GetPosition();
}
