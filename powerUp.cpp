#include "powerUp.h"
#include "game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Breakout {

    PowerUp::PowerUp(const sf::Vector2f& pos, const int type) 
        : powerUpCircle(sf::CircleShape(powerUpRadius)), type{type}
    {
        powerUpCircle.setFillColor(powerUpColors[type]);
        powerUpCircle.setOrigin(sf::Vector2f(powerUpRadius, powerUpRadius));
        powerUpCircle.setPosition(pos);
    }
    
    PowerUp::PowerUp(const sf::Vector2f& pos) 
        : powerUpCircle(sf::CircleShape(powerUpRadius)), type{rand() % typeCount}
    {
        powerUpCircle.setFillColor(powerUpColors[int(type)]);
        powerUpCircle.setOrigin(sf::Vector2f(powerUpRadius, powerUpRadius));
        powerUpCircle.setPosition(pos);
    }

    bool PowerUp::move(const float dt) {
        powerUpCircle.move(0, powerUpSpeed * dt);
        if (powerUpCircle.getPosition().y > screenHeight + powerUpRadius) return true;
        return false;
    }
}