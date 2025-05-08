#pragma  once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include "game.h"

namespace Breakout {

    const std::string startMenuTitle = "Breakout";
    const std::string startButtonText = "Start";
    const std::string quitButtonText = "Quit";

    const sf::Vector2f startButtonSize = sf::Vector2f(200, 80);
    const sf::Vector2f quitButtonSize = sf::Vector2f(200, 80);

    const sf::Vector2f titlePos = sf::Vector2f(halfScreenWidth, 150);
    const sf::Vector2f startButtonPos = sf::Vector2f(halfScreenWidth, 300);
    const sf::Vector2f quitButtonPos = sf::Vector2f(halfScreenWidth, 450);

    const int titleFontSize = 60;
    const int textFontSize = 30;

    const int startType = 0;
    const int quitType = 1;

    const int quit = -1;
    const int start = 0;

    struct Button {
        sf::RectangleShape rect;
        sf::Text text;

        void drawButton(sf::RenderWindow& window) {
            window.draw(rect);
            window.draw(text);
        }

        bool isClicked(sf::RenderWindow& window, sf::Event event) {
            if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                return rect.getGlobalBounds().contains(mousePos);
            }
            return false;
        }
    };

    class StartMenu {
        public:
            StartMenu();

            int playStartMenu(sf::RenderWindow& window, sf::Event event);
            void drawStartMenu(sf::RenderWindow& window);
            bool startClicked(sf::RenderWindow& window, sf::Event event);
            bool quitClicked(sf::RenderWindow& window, sf::Event event);
            void moveSelectedDown();
            void moveSelectedUp();
            void chooseSelected();
        private:
            sf::Font font;
            sf::Text title;
            Button startButton;
            Button quitButton;
            sf::RectangleShape selected;
            int selectedType = 0;
    };

    inline bool StartMenu::startClicked(sf::RenderWindow& window, sf::Event event) {
        return startButton.isClicked(window, event);
    }

    inline bool StartMenu::quitClicked(sf::RenderWindow& window, sf::Event event) {
        return quitButton.isClicked(window, event);
    }
}