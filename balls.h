#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <vector>
#include "blocks.h"


namespace Breakout {

    const int ballRadius = 10;
    const float ballSpeed = 400;
    const int deadBall = -1;

    const sf::Color ballColor = sf::Color::White;

    class Ball {
        public:
            Ball(sf::Vector2f startVel, sf::Vector2f startPos);
            Ball();

            int move(const sf::RectangleShape& platform, std::vector<Block>& blocks, const float dt);
            sf::CircleShape& getCircle();
            void deleteBall();

        private:
            sf::CircleShape m_circle;
            sf::Vector2f m_velocity;
            sf::Vector2f m_nextPos; 
            

            void hitWall();
            void hitPlatform(const sf::RectangleShape& platform);
            int hitBottom();
            int hitBlock(std::vector<Block>& blocks);
    };


    inline sf::CircleShape& Ball::getCircle() {
        return m_circle;
    }
}