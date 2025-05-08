#pragma  once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "balls.h"
#include "powerUp.h"
#include "game.h"

namespace Breakout {

    const int platformSpeed = 300;
    const int platformWidth = 100;
    const int platformHeight = 20;

    const sf::Vector2f startPos = sf::Vector2f(halfScreenWidth, screenHeight - 40);
    const sf::Color platformColor = sf::Color::White;

    const float powerUpDuration = 5.f;
    const float laserSpeed = 150;
    const sf::Vector2f laserSize = sf::Vector2f(5, 15);

    struct ActivePUp {
        PUpType type;
        float remaining;
        float factor;
        float laserCooldown = 0.f;
    };

    class Platform {
        public:
            Platform();
            Platform(const sf::Vector2f& startPos);

            void move(const float dt, const int dir);
            int hitPowerUp(std::vector<PowerUp>& powerUps);
            void applyPowerUp(PUpType powerUpType, std::vector<Ball>& balls);
            int update(float dt, std::vector<Block>& blocks);

            sf::RectangleShape& getRect();
            float getWidth();
            float getSpeed();
            std::vector<sf::RectangleShape>& getLasers();
        private:
            float widthMultiplier;
            float speedMultiplier;
            sf::RectangleShape platformRect;
            std::vector<sf::RectangleShape> lasers;
            std::vector<ActivePUp> activePUps;

            void revertEffect(const ActivePUp& p);
            int moveLaser(sf::RectangleShape& laser, float dt, std::vector<Block>& blocks);
    };  

    inline sf::RectangleShape& Platform::getRect() {
        return platformRect;
    }

    inline float Platform::getWidth() {
        return platformWidth * widthMultiplier;
    }

    inline float Platform::getSpeed() {
        return platformSpeed * speedMultiplier;
    }

    inline std::vector<sf::RectangleShape>& Platform::getLasers() {
        return lasers;
    }
}