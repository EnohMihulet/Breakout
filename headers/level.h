#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "balls.h"
#include "blocks.h"
#include "platform.h"
#include "powerUp.h"

namespace Breakout {

    const int win = 0;
    const int loss = 1;
    const int inProgress = 2;

    class Level {
        public: 
            Level();

            Platform& getPlatform();
            std::vector<Ball>& getBalls();
            std::vector<PowerUp>& getPowerUps();
            std::vector<Block>& getBlocks();

            void startGame(const int levelIndex);
            void play();
            void drawLevel(sf::RenderWindow& window);
            int levelState();

        private:
            sf::Clock levelClock;
            Platform platform;
            std::vector<Ball> balls;
            std::vector<PowerUp> powerUps;
            std::vector<Block> blocks;
            float dt = 0;

            void movePowerups();
            void handleInput();
            void moveBalls();
            void updatePowerUps();
            void updatePlatform();
            void generateBlocks(const int levelIndex);
    };

    inline Platform& Level::getPlatform() {
        return platform;
    }

    inline std::vector<Ball>& Level::getBalls() {
        return balls;
    }

    inline std::vector<PowerUp>& Level::getPowerUps() {
        return powerUps;
    }

    inline std::vector<Block>& Level::getBlocks() {
        return blocks;
    }


    const std::vector<std::vector<int>> level1 = {
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0}
    };

    const std::vector<std::vector<int>> level2 = {
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0}
    };
    
    const std::vector<std::vector<int>> level3 = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };

    const std::vector<std::vector<std::vector<int>>> levels = {level1, level2, level3};
}