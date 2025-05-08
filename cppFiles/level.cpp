#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../headers/level.h"
#include "../headers/game.h"
#include "../headers/platform.h"
#include "../headers/powerUp.h"

namespace Breakout {
    Level::Level() 
        : platform()
    {
        balls.push_back(Ball());
    }

    void Level::generateBlocks() {
        int blockNum = screenWidth / (blockWidth + blockGap);
        int sideOffset = (screenWidth % (blockWidth + blockGap)) / 2;
        int xpos = sideOffset + (blockWidth / 2);
        for (int y = 1; y < 6; ++y) {
            for (int i = 0; i < blockNum; ++i) {
                sf::Vector2f pos = sf::Vector2f(xpos + (blockWidth + blockGap) * i, y * (blockHeight + blockGap));
                Block block = Block(pos, y, i, 0, colors[y - 1]);
                blocks.push_back(block);
            }
        }
    }

    void Level::movePowerups() {
        for (PowerUp& p : powerUps) p.move(dt);
    }

    void Level::handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            platform.move(dt, -1);
        }   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            platform.move(dt, 1);
        }
    }
 
    void Level::moveBalls() {
        for (size_t i = 0; i < balls.size(); ++i) {
            int moveVal = balls[i].move(platform.getRect(), blocks, dt);
            if (moveVal == success)
                continue;
            if (moveVal == deadBall)
                balls.erase(balls.begin() + i);
            else {
                if (rand() % 2 == 1) powerUps.push_back(PowerUp(blocks[moveVal].getRect().getPosition()));
                blocks.erase(blocks.begin() + moveVal);
            }  
        }
    }

    void Level::updatePowerUps() {
        const int hitPowerUpIndex = platform.hitPowerUp(powerUps);
        if (hitPowerUpIndex != success) {
            PUpType powerUpType = powerUps[hitPowerUpIndex].getType();
            powerUps.erase(powerUps.begin() + hitPowerUpIndex);

            platform.applyPowerUp(powerUpType, balls);
        }
        for (PowerUp& p : powerUps) p.move(dt);
    }

    void Level::updatePlatform() {
        int blockIndex = platform.update(dt, blocks);
        if (blockIndex == success) return;
        blocks.erase(blocks.begin() + blockIndex);
    }

    void Level::play() {
        dt = levelClock.restart().asSeconds();

        handleInput();

        moveBalls();

        updatePowerUps();

        updatePlatform();
    }

    void Level::drawLevel(sf::RenderWindow& window) {
        window.draw(platform.getRect());
        for (sf::RectangleShape& l : platform.getLasers()) window.draw(l);
        for (Ball& b : balls) window.draw(b.getCircle());
        for (Block& b : blocks) window.draw(b.getRect());
        for (PowerUp& p : powerUps) window.draw(p.getCircle());
    }

    int Level::levelState() {
        if (balls.size() == 0) return loss;
        if (blocks.size() == 0) return win;
        return inProgress;
    }
}