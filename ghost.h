#include <SFML/Graphics.hpp>
#include <cmath>
const int GHOST_SIZE = 50;


class Ghost {
public:
    Ghost(int x, int y, sf::Color color) : x(x), y(y) {
        //triangle-shaped
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(0, 0));
        shape.setPoint(1, sf::Vector2f(GHOST_SIZE, 0));
        shape.setPoint(2, sf::Vector2f(GHOST_SIZE / 2, GHOST_SIZE));
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);
        shape.setOrigin(GHOST_SIZE / 2, GHOST_SIZE / 2);
    }

    void draw(sf::RenderWindow& window) {
        shape.setPosition(x * GHOST_SIZE + GHOST_SIZE / 2, y * GHOST_SIZE + GHOST_SIZE / 2);
        window.draw(shape);
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }

private:
    int x;
    int y;
    sf::ConvexShape shape;
};
