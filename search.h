#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

struct Node {
    int x, y;
    int cost; //(heuristic)
};

bool operator<(const Node& a, const Node& b) {
    return a.cost > b.cost;
}

//Greedy algorithm
//each move greedy, returs first found path
std::vector<std::pair<int, int>> findPathGreedy(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> destination) {
    int numRows = maze.size();
    int numCols = maze[0].size();
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 

    std::priority_queue<Node> frontier;
    frontier.push({start.first, start.second, 0});

    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));
    std::vector<std::vector<std::pair<int, int>> > cameFrom(numRows, std::vector<std::pair<int, int>>(numCols, {-1, -1}));

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.x == destination.first && current.y == destination.second) {//if reached finish returning path
            std::vector<std::pair<int, int>> path;
            std::pair<int, int> currentPoint = {destination.first, destination.second};
            while (currentPoint != start) {
                path.push_back(currentPoint);
                currentPoint = cameFrom[currentPoint.first][currentPoint.second];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        visited[current.x][current.y] = true;

        for (const auto& direction : directions) {
            int newX = current.x + direction.first;
            int newY = current.y + direction.second;

            if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && maze[newX][newY] == 0 && !visited[newX][newY]) {
                int heuristic = std::abs(newX - destination.first) + std::abs(newY - destination.second);  
                frontier.push({newX, newY, heuristic});
                cameFrom[newX][newY] = {current.x, current.y};
            }
        }
    }

    // No path found
    return {};
}

// A* algorithm
std::vector<std::pair<int, int>> findPathAStar(const std::vector<std::vector<int>>& maze, std::pair<int, int> start, std::pair<int, int> destination) {
    int numRows = maze.size();
    int numCols = maze[0].size();
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 

    std::priority_queue<Node> frontier;
    frontier.push({start.first, start.second, 0});

    std::vector<std::vector<int>> costSoFar(numRows, std::vector<int>(numCols, INT_MAX));
    costSoFar[start.first][start.second] = 0;
    std::vector<std::vector<std::pair<int, int>>> cameFrom(numRows, std::vector<std::pair<int, int>>(numCols, {-1, -1}));

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.x == destination.first && current.y == destination.second) {
            std::vector<std::pair<int, int>> path;
            std::pair<int, int> currentPoint = {destination.first, destination.second};
            while (currentPoint != start) {
                path.push_back(currentPoint);
                currentPoint = cameFrom[currentPoint.first][currentPoint.second];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& direction : directions) {
            int newX = current.x + direction.first;
            int newY = current.y + direction.second;

            if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && maze[newX][newY] == 0) {
                int newCost = costSoFar[current.x][current.y] + 1;
                if (newCost < costSoFar[newX][newY]) {
                    costSoFar[newX][newY] = newCost;
                    int heuristic = newCost + std::abs(newX - destination.first) + std::abs(newY - destination.second);  // A* heuristic
                    frontier.push({newX, newY, heuristic});
                    cameFrom[newX][newY] = {current.x, current.y};
                }
            }
        }
    }

    // No path found
    return {};
}
