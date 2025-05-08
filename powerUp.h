#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Breakout {

    const int powerUpRadius = 5;
    const int powerUpSpeed = 50;
    const int typeCount = 4;
    const std::vector<sf::Color> powerUpColors{sf::Color::Yellow, sf::Color::Green, sf::Color::Magenta, sf::Color::Blue};

    enum class PUpType {
        Expand,
        ExtraBall,
        Speed,
        Lasers
    };

    class PowerUp {
        public:
            PowerUp(const sf::Vector2f& pos, int type);
            PowerUp(const sf::Vector2f& pos);

            sf::CircleShape& getCircle();
            bool move(const float dt);
            PUpType getType();

        private:
            sf::CircleShape powerUpCircle;
            PUpType type;
    };

    inline sf::CircleShape& PowerUp::getCircle() {
        return powerUpCircle;
    }

    inline PUpType PowerUp::getType() {
        return type;
    }
}