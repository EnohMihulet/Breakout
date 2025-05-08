#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <climits>
#include <cmath>
#include <cstdlib>
#include "game.h"
#include "level.h"
#include "startMenu.h"

using namespace Breakout;

int main() {
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Breakout");
    
    std::string gameState = "Start";
    Level level;
    
    StartMenu startMenu = StartMenu();

    // MAIN LOOP
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); // Close window
        }

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