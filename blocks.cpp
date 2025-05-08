#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "blocks.h"

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