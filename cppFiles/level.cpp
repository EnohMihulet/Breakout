#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "../headers/level.h"
#include "../headers/game.h"
#include "../headers/platform.h"
#include "../headers/powerUp.h"

namespace Breakout {
    Level::Level(){}
    void Level::startGame(const int levelIndex) {
        blocks.clear();
        powerUps.clear();
        balls.clear();
        dt = levelClock.restart().asSeconds();
        platform = Platform();
        balls.push_back(Ball());
        generateBlocks(levelIndex);
    }

    void Level::generateBlocks(const int levelIndex) {
        int sideOffset = (screenWidth % (blockWidth + blockGap)) / 2;
        int xpos = sideOffset + (blockWidth / 2);
        auto levelGrid = levels[levelIndex];
        for (int y = 0; y < int(levelGrid.size()); ++y) {
            for (int i = 0; i < int(levelGrid[y].size()); ++i) {
                if (levelGrid[y][i] == 0) continue;
                sf::Vector2f pos = sf::Vector2f(xpos + (blockWidth + blockGap) * i, (y+1) * (blockHeight + blockGap));
                Block block = Block(pos, (y+1), i, 0, colors[y]);
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