#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "game.h"
#include "startMenu.h"

namespace Breakout {

    const sf::Vector2f levelButtonSize(100, 50);
    const sf::Vector2f levelButtonStartPos(halfScreenWidth, 300);

    class LevelSelectMenu {
        public:
            LevelSelectMenu(const sf::Font& font);

            int playLevelMenu(sf::RenderWindow& window, sf::Event& event);
            void drawLevelMenu(sf::RenderWindow& window);
            int levelClicked(sf::RenderWindow &window, sf::Event& event);
            void moveSelectedDown();
            void moveSelectedUp();

        private:
            sf::Font font;
            sf::Text title;
            std::vector<Button> levels;
            Button level1;
            sf::RectangleShape selected;
            int selectedIndex = 0;
            bool getInput = false;
    };
};