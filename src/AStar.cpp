#include "AStar.h"
#include <queue>
#include <map>
#include "SDL_SimpleApp.h"

AStar::AStar()
{
}

std::vector<Vector2D> AStar::CalculatePath(Node* initialPos, Node* targetPos)
{
	//Extret de: https://newbedev.com/java-how-to-override-the-priority-queue-comparator-c-code-example
	auto compare = [](std::pair<Node*, int> a, std::pair<Node*, int> b) {
		return a.second > b.second;
	};


	std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, decltype(compare)> frontier(compare);

	frontier.push(std::make_pair(initialPos, 0));

	std::map < Node*, Node* > came_from = {};
	std::map<Node*, int> cost_so_far{};
	came_from[initialPos] = nullptr;
	cost_so_far[initialPos] = 0;

	int counter = 1;

	while (!frontier.empty()) {
		Node* current = frontier.top().first;
		frontier.pop();

		if (current == targetPos)break; //early exit

		std::vector<Node*> currentNeighbours = current->GetNeighbours();

		for (int i = 0; i < currentNeighbours.size(); i++) {
			int new_cost = cost_so_far[current] + currentNeighbours[i]->GetWeight();

			if (cost_so_far.find(currentNeighbours[i]) == cost_so_far.end()
				|| new_cost < cost_so_far[currentNeighbours[i]]) {

				cost_so_far[currentNeighbours[i]] = new_cost;

				int priority = new_cost + (int)ManhattanDistanceHeuristic(targetPos->GetPosition(), currentNeighbours[i]->GetPosition());

				frontier.push(std::make_pair(currentNeighbours[i], priority));
				counter++;
				std::cout << counter << std::endl;
				came_from[currentNeighbours[i]] = current;
			}
		}
	}


	//Recuperar el camí
	Node* current = targetPos;
	std::vector<Vector2D> path;
	path.push_back(cell2pix(targetPos->GetPosition()));

	while (current != initialPos) {
		current = came_from[current];
		path.push_back(cell2pix(current->GetPosition()));
	}

	std::reverse(path.begin(), path.end());

	return path;

}

Vector2D AStar::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
}

float AStar::ManhattanDistanceHeuristic(Vector2D n1, Vector2D n2)
{
	float dx = abs(n1.x - n2.x);
	float dy = abs(n1.y - n2.y);
	return (dx + dy);
}
