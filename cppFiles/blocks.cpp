#include "../headers/blocks.h"

namespace Breakout {


    Block::Block(sf::Vector2f pos, int row, int col, int type, sf::Color color)
        : blockRect(sf::RectangleShape(sf::Vector2f(blockWidth, blockHeight))), row{row}, col{col}, type{type}, color{color}
    {
        blockRect.setOrigin(sf::Vector2f(blockWidth / 2.f, blockHeight / 2.f));
        blockRect.setPosition(pos);
        blockRect.setFillColor(color);
    }
    
    Block::Block(sf::Vector2f pos, int row, int col, int type)
        : blockRect(sf::RectangleShape(sf::Vector2f(blockWidth, blockHeight))), row{row}, col{col}, type{type}, color{sf::Color::Yellow}
    {
        blockRect.setOrigin(sf::Vector2f(blockWidth / 2.f, blockHeight / 2.f));
        blockRect.setPosition(pos);
        blockRect.setFillColor(color);
    }
} 