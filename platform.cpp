#include "platform.h"
#include "balls.h"
#include "game.h"
#include "powerUp.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <vector>

namespace Breakout {

    Platform::Platform() 
        : widthMultiplier(1.0), speedMultiplier(1.0), platformRect(sf::RectangleShape(sf::Vector2f(getWidth(), platformHeight)))
    {
        platformRect.setOrigin(getWidth() / 2.f, platformHeight / 2.f);
        platformRect.setFillColor(platformColor);
        platformRect.setPosition(startPos);
    }

    Platform::Platform(const sf::Vector2f& pos) 
        : widthMultiplier(1.0), speedMultiplier(1.0), platformRect(sf::RectangleShape(sf::Vector2f(getWidth(), platformHeight)))
    {
        platformRect.setOrigin(getWidth() / 2.f, platformHeight / 2.f);
        platformRect.setFillColor(platformColor);
        platformRect.setPosition(pos);
    }

    void Platform::move(const float dt, const int dir) {
        sf::Vector2f nextPos = platformRect.getPosition() + sf::Vector2f(getSpeed() * dt * dir, 0);

        nextPos.x = std::max(getWidth() / 2.f, std::min(screenWidth - getWidth() / 2.f, nextPos.x));
        platformRect.setPosition(nextPos);    
    }

    int Platform::hitPowerUp(std::vector<PowerUp>& powerUps) {
        for (size_t i = 0; i < powerUps.size(); i++) {
            if (platformRect.getGlobalBounds().intersects(powerUps[i].getCircle().getGlobalBounds())) {
                return int(i);
            }
        }
        return success;
    }

    void Platform::applyPowerUp(PUpType type, std::vector<Ball>& balls) {

        if (type == PUpType::ExtraBall) {
            balls.push_back(Ball());
            return;
        }
        ActivePUp p;
        p.type = type;
        p.remaining = powerUpDuration;
        if (type == PUpType::Expand) {
            p.factor = 1.5f;
            widthMultiplier *= 1.5f;
            platformRect.setSize({ getWidth(), platformHeight });
            platformRect.setOrigin(getWidth()/2.f, platformHeight/2.f);
        }
        else if (type == PUpType::Speed) {
            p.factor = 1.5f;
            speedMultiplier *= 1.5f;
        }
        activePUps.push_back(p);
    }

    void Platform::revertEffect(const ActivePUp& p) {
        if (p.type == PUpType::Expand) {
            widthMultiplier /= p.factor;
            platformRect.setSize({ getWidth(), platformHeight });
            platformRect.setOrigin(getWidth()/2.f, platformHeight/2.f);
        }
        else if (p.type == PUpType::Speed) {
            speedMultiplier /= p.factor;
        }
    }

    void Platform::update(float dt) {
        for (int i = 0; i < int(activePUps.size()); ++i) {
            activePUps[i].remaining -= dt;
            if (activePUps[i].remaining <= 0) {
                revertEffect(activePUps[i]);
                activePUps.erase(activePUps.begin() + i);
                return;
            }
        }
    }
}