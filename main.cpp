#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include "ghost.h"
#include "search.h"
#include "mazes.h"

const int CELL_SIZE = 50;
//Chose maze
std::pair<std::vector<std::vector<int>>, std::vector<int>> maze_pos = mash;
std::vector<std::vector<int>> maze = maze_pos.first;
const int MAZE_HEIGHT = maze.size();
const int MAZE_WIDTH = maze[0].size();

const int WINDOW_WIDTH = MAZE_WIDTH * CELL_SIZE;
const int WINDOW_HEIGHT = MAZE_HEIGHT * CELL_SIZE;

int pacmanY = maze_pos.second[0];
int pacmanX = maze_pos.second[1];
int G1X = maze_pos.second[3];
int G1Y = maze_pos.second[2];
int G2X = maze_pos.second[5];
int G2Y = maze_pos.second[4];



int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pac-Man");
    sf::Clock clock;
    float deltaTime = 0.0f;
    const float GHOST_SPEED = 2.0f; 

    //Pac-Man aka Yellow circle
    sf::CircleShape pacman(CELL_SIZE / 2);
    pacman.setFillColor(sf::Color::Yellow);
    pacman.setOrigin(CELL_SIZE / 2, CELL_SIZE / 2);

    //Ghost objects
    Ghost ghost1(G1X, G1Y, sf::Color::Red);
    Ghost ghost2(G2X, G2Y, sf::Color::Green);

    std::vector<std::pair<int, int>> pathGhost1; //path for first ghost
    std::vector<std::pair<int, int>> pathGhost2; //path for second ghost

    int prevPacmanX = -1;
    int prevPacmanY = -1;
    int step = 1; //where are we on the path

    while (window.isOpen()) {
        
        sf::Time elapsed = clock.restart();
        deltaTime += elapsed.asSeconds();

        while (deltaTime >= (1.0f / GHOST_SPEED)) {

            std::pair<int, int> ghost1Directions;
            std::pair<int, int> ghost2Directions;

            if (pacmanX != prevPacmanX || pacmanY != prevPacmanY){//if Pac-Man moved
                prevPacmanX = pacmanX;
                prevPacmanY = pacmanY;
                step = 1;
                //Greedy Search for RED
                pathGhost1 = findPathGreedy(maze, {ghost1.getY(), ghost1.getX()}, {pacmanY, pacmanX});
                //A* for Green
                pathGhost2 = findPathAStar(maze, {ghost2.getY(), ghost2.getX()}, {pacmanY, pacmanX});
            }
            else step++;//if pac-man stayed in place continue on prev path

                if (pathGhost1.size() > step) {
                    ghost1Directions = pathGhost1[step];
                    
                } else {
                    ghost1Directions.first = ghost1.getY();
                    ghost1Directions.second = ghost1.getX();
                }
                
                if (pathGhost2.size() > step) {
                    ghost2Directions = pathGhost2[step];
                } else {
                    ghost2Directions.first = ghost2.getY();
                    ghost2Directions.second = ghost2.getX();
                }

            // Updated ghost's positions
            ghost1.setY(ghost1Directions.first);
            ghost1.setX(ghost1Directions.second);

            ghost2.setY(ghost2Directions.first);
            ghost2.setX(ghost2Directions.second);

            deltaTime -= (1.0f / GHOST_SPEED);
        }

        // Pac-man Controls
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && maze[pacmanY - 1][pacmanX] == 0) {
                    pacmanY--;
                } else if (event.key.code == sf::Keyboard::Down && maze[pacmanY + 1][pacmanX] == 0) {
                    pacmanY++;
                } else if (event.key.code == sf::Keyboard::Left && maze[pacmanY][pacmanX - 1] == 0) {
                    pacmanX--;
                } else if (event.key.code == sf::Keyboard::Right && maze[pacmanY][pacmanX + 1] == 0) {
                    pacmanX++;
                }
            }
        }


        // Clear the window
        window.clear();

        // Draw the maze
        for (int i = 0; i < MAZE_HEIGHT; i++) {
            for (int j = 0; j < MAZE_WIDTH; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                if (maze[i][j] == 1) {
                    cell.setFillColor(sf::Color::Blue);
                } else {
                    cell.setFillColor(sf::Color::Black);
                }
                window.draw(cell);
            }
        }

        // Draw the path of RED
        for (const auto& point : pathGhost1) {
            sf::CircleShape pathDot(CELL_SIZE / 6);
            pathDot.setFillColor(sf::Color::Red); 
            pathDot.setOrigin(pathDot.getRadius(), pathDot.getRadius());
            pathDot.setPosition(point.second * CELL_SIZE + CELL_SIZE / 2 - 4, point.first * CELL_SIZE + CELL_SIZE / 2 - 4);
            window.draw(pathDot);
        }

        // Draw the path of Green
        for (const auto& point : pathGhost2) {
            sf::CircleShape pathDot(CELL_SIZE / 6); 
            pathDot.setFillColor(sf::Color::Green); 
            pathDot.setOrigin(pathDot.getRadius(), pathDot.getRadius());
            pathDot.setPosition(point.second * CELL_SIZE + CELL_SIZE / 2 + 4, point.first * CELL_SIZE + CELL_SIZE / 2 + 4);
            window.draw(pathDot);
        }

        // Draw Pac-Man
        pacman.setPosition(pacmanX * CELL_SIZE + CELL_SIZE / 2, pacmanY * CELL_SIZE + CELL_SIZE / 2);
        window.draw(pacman);

        // Draw the ghosts
        ghost1.draw(window);
        ghost2.draw(window);

        window.display();
    }

    return 0;
}
