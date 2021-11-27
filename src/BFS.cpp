#include "BFS.h"
#include <queue>
#include <map>

std::vector<Vector2D> BFS::CalculatePath(Node* initialPos, Node* targetPos)
{
    std::queue<Node*> frontier;
    frontier.push(initialPos);
    std::map<Node*, Node*> came_from = {};
    came_from[initialPos] = nullptr;

    //recorrent fins a trobar el node target
    while (!frontier.empty()) {
        Node* current = frontier.front();
        frontier.pop();

        std::vector<Node*> currentNeighbours = current->GetNeighbours();

        //early exit
        if (current == targetPos)break;

        for (int i = 0; i < currentNeighbours.size(); i++) {
            //busquem al mapa si s'ha visitat el veí (node)
            if (came_from.find(currentNeighbours[i]) == came_from.end()) {
                frontier.push(currentNeighbours[i]);
                came_from[currentNeighbours[i]] = current;
            }
        }

    }

    //Recuperar el camí
    Node* current = targetPos;
    std::vector<Vector2D> path;
    path.push_back(targetPos->GetPosition());

    while (current != initialPos) {
        current = came_from[current];
        path.push_back(current->GetPosition());
    }

    std::reverse(path.begin(), path.end());

    return path;

}
