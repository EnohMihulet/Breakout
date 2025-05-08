#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

namespace Breakout {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int halfScreenWidth = 400;
    const int halfScreenHeight = 300;
    const int success = -2;

    float dot(const sf::Vector2f& a, const sf::Vector2f& b);
    float magnitude(const sf::Vector2f& a);
    sf::Vector2f reflectionVector(const sf::Vector2f& a, const sf::Vector2f& b);
    sf::Vector2f normalizedVector(const sf::Vector2f& a);
}