#include <cmath>
#include <random>
#include "../headers/game.h"
#include "../headers/balls.h"

namespace Breakout {

    static std::mt19937_64 rng{ std::random_device{}() };

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
        static std::uniform_real_distribution<float> dist(-3.14/4.f, 3.14/4.f);
        float offset = dist(rng);

        float x = std::sin(offset) * ballSpeed;
        float y = -std::cos(offset) * ballSpeed;
        return sf::Vector2f{x, y};
    } 
}