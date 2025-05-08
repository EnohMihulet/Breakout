#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
namespace Breakout {

    const int blockWidth = 50;
    const int blockHeight = 20;
    const int blockGap = 5;

    const std::vector<sf::Color> colors{sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, ::sf::Color::Green, sf::Color::Magenta};

    class Block {
        public:
            Block(sf::Vector2f pos, int row, int col, int type, sf::Color color);
            Block(sf::Vector2f pos, int row, int col, int type);

            sf::RectangleShape& getRect();
        private:
            sf::RectangleShape blockRect;
            int row;
            int col;
            int type;
            sf::Color color;
    };

    inline sf::RectangleShape& Block::getRect() {
        return blockRect;
    }
}