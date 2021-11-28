#include "BFS.h"
#include <queue>
#include <map>
#include "SDL_SimpleApp.h"

BFS::BFS()
{
}

std::vector<Vector2D> BFS::CalculatePath(Node* initialPos, Node* targetPos)
{
    std::queue<Node*> frontier;
    frontier.push(initialPos);
    std::map<Node*, Node*> came_from = {};
    came_from[initialPos] = nullptr;

    int counter = 1;

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

Vector2D BFS::cell2pix(Vector2D cell)
{
    int offset = CELL_SIZE / 2;
    return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
}

