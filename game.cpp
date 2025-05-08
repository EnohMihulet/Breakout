#include "game.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

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
}