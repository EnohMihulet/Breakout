#include "../headers/level.h"
#include "../headers/startMenu.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>

using namespace Breakout;

int main() {
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Breakout");
    
    std::string gameState = "Start";
    Level level;
    
    StartMenu startMenu = StartMenu();
    sf::Clock gameClock;
    gameClock.restart();

    // MAIN LOOP
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); // Close window
        }
        if (gameClock.getElapsedTime().asSeconds() <= .1) continue;

        if (gameState == "Start") {
            int startMenuVal = startMenu.playStartMenu(window, event);
            if (startMenuVal == start) {
                level = Level();
                level.generateBlocks();
                gameState = "Play";
            }
            else if (startMenuVal == quit) window.close();
            
            window.clear();
            startMenu.drawStartMenu(window);
            window.display();
        }
        else {
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