#include <cmath>
#include "../headers/game.h"
#include "../headers/balls.h"

namespace Breakout {

    float dot(const sf::Vector2f& a, const sf::Vector2f& b) {
        return a.x * b.x + a.y * b.y;
    }

    float magnitude(const sf::Vector2f& a) {
        return sqrt(a.x * a.x + a.y * a.y);
    }

    sf::Vector2f reflectionVector(const sf::Vector2f &a, const sf::Vector2f &b) {
        return a - 2.f * (dot(a, b) * b);
    }

    sf::Vector2f normalizedVector(const sf::Vector2f& a) {
        return a / magnitude(a);
    }

    sf::Vector2f getRandomVelocity() {
        int x = rand() % (int(ballSpeed) - 200);     
        int y = rand() % (int(ballSpeed));
        int dir = rand() % 2 == 1 ? 1 : -1;
        return normalizedVector(sf::Vector2f(x * dir,y)) * ballSpeed;
    }
}