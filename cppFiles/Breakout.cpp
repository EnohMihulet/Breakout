#include "../headers/level.h"
#include "../headers/startMenu.h"
#include "../headers/levelSelectMenu.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>

using namespace Breakout;

int main() {
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Breakout");
    
    std::string gameState = "Start";
    StartMenu startMenu = StartMenu();
    Level level = Level();
    LevelSelectMenu levelSelectMenu(startMenu.font);

    sf::Clock gameClock;
    gameClock.restart();

    // MAIN LOOP
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); // Close window
            if (gameState == "Start") {
                int startMenuVal = startMenu.playStartMenu(window, event);
                if (startMenuVal == start) {
                    levelSelectMenu = LevelSelectMenu(startMenu.font);
                    gameState = "Levels";
                }
                else if (startMenuVal == quit) window.close();
                
                window.clear();
                startMenu.drawStartMenu(window);
                window.display();
            }
            else if (gameState == "Levels") {
                int levelIndex = levelSelectMenu.playLevelMenu(window, event);
                if (levelIndex != -1) {
                    level.startGame(levelIndex); 
                    gameState = "Play";
                }
                window.clear();
                levelSelectMenu.drawLevelMenu(window);
                window.display();
            }
        }
        if (gameState == "Play") {
            level.play();
            if (level.levelState() == win) {
                gameState = "Start";
            }
            else if (level.levelState() == loss) {
                gameState = "Start";
            }
            window.clear();
            level.drawLevel(window);
            window.display();
        }
    }
    return 0;
}