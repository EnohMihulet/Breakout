#include "../headers/platform.h"
#include "../headers/game.h"
#include "../headers/powerUp.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
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
            balls.push_back(Ball(
                getRandomVelocity(), 
                sf::Vector2f(platformRect.getPosition().x, platformRect.getPosition().y - platformHeight)));
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

    int Platform::moveLaser(sf::RectangleShape& laser, float dt, std::vector<Block>& blocks) {
        sf::Vector2f nextPos = laser.getPosition() + sf::Vector2f(0, -laserSpeed * dt);
        for (int i = 0; i < int(blocks.size()); ++i) {
            if (blocks[i].getRect().getGlobalBounds().intersects(laser.getGlobalBounds())) {
                return i;
            }
            if (nextPos.y <= 0) {
                return -1;
            }
        }
        laser.setPosition(nextPos);
        return success;
    }

    int Platform::update(float dt, std::vector<Block>& blocks) {
        for (auto it = activePUps.begin(); it != activePUps.end(); ) {
            it->remaining -= dt;
    
            if (it->type == PUpType::Lasers) {
                it->laserCooldown += dt;
    
                // Fire laser every 0.8 seconds
                if (it->laserCooldown >= 0.8f) {
                    it->laserCooldown = 0.f;
    
                    sf::RectangleShape laser(laserSize);
                    laser.setPosition(platformRect.getPosition());
                    laser.setFillColor(sf::Color::Red);
    
                    lasers.push_back(laser);
                }
            }
    
            if (it->remaining <= 0.f) {
                revertEffect(*it);
                it = activePUps.erase(it);
            } else {
                ++it;
            }
        }
    
        for (auto it = lasers.begin(); it != lasers.end(); ) {
            int blockIndex = moveLaser(*it, dt, blocks);
            if (blockIndex == -1) {
                it = lasers.erase(it);
            } 
            else if (blockIndex != success) {
                lasers.erase(it);
                return blockIndex;
            }
            else {
                ++it;
            }
        }
    
        return success;
    }
}