#pragma  once
#include "balls.h"
#include "powerUp.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "game.h"

namespace Breakout {

    const int platformSpeed = 300;
    const int platformWidth = 100;
    const int platformHeight = 20;

    const sf::Vector2f startPos = sf::Vector2f(halfScreenWidth, screenHeight - 40);
    const sf::Color platformColor = sf::Color::White;

    const float powerUpDuration = 5.f;

    struct ActivePUp {
        PUpType type;
        float remaining;
        float factor;
    };

    class Platform {
        public:
            Platform();
            Platform(const sf::Vector2f& startPos);

            void move(const float dt, const int dir);
            int hitPowerUp(std::vector<PowerUp>& powerUps);
            void applyPowerUp(PUpType powerUpType, std::vector<Ball>& balls);
            void update(float dt);

            sf::RectangleShape& getRect();
            float getWidth();
            float getSpeed();
        private:
            float widthMultiplier;
            float speedMultiplier;
            sf::RectangleShape platformRect;
            std::vector<sf::RectangleShape> lasers;
            std::vector<ActivePUp> activePUps;

            void revertEffect(const ActivePUp& p);
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
}