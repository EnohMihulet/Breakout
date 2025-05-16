#include "../headers/levelSelectMenu.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>
#include <vector>

namespace Breakout {

    LevelSelectMenu::LevelSelectMenu(const sf::Font& font) {
    
        title.setFont(font);
        title.setString(startMenuTitle);
        title.setCharacterSize(titleFontSize);
        title.setFillColor(sf::Color::White);
        title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
        title.setPosition(titlePos);
    
        // Let's say you want 3 levels
        const int numLevels = 3;
        sf::Color textColor = sf::Color::Black;
    
        for (int i = 0; i < numLevels; ++i) {
            Button levelButton = Button();
    
            levelButton.rect.setSize(levelButtonSize);
            levelButton.rect.setOrigin(levelButtonSize / 2.f);
            levelButton.rect.setPosition(levelButtonStartPos + sf::Vector2f(0, i * 100));
            levelButton.rect.setFillColor(sf::Color::Transparent);
    
            std::stringstream text;
            text << "Level " << i + 1;
            levelButton.text.setFont(font);
            levelButton.text.setString(text.str());
            levelButton.text.setCharacterSize(textFontSize);
            sf::FloatRect bounds = levelButton.text.getLocalBounds();
            levelButton.text.setOrigin(
                bounds.left + bounds.width / 2.f,
                bounds.top + bounds.height / 2.f
            );
            levelButton.text.setPosition(levelButton.rect.getPosition());
            levelButton.text.setFillColor(textColor);
    
            levels.push_back(levelButton);
            textColor = sf::Color::White;
        }
    
        selectedIndex = 0;
        selected.setSize(sf::Vector2f(screenWidth, 100));
        selected.setOrigin(sf::Vector2f(halfScreenWidth, 50));
        selected.setPosition(levels[0].rect.getPosition());
        selected.setFillColor(sf::Color::White);
    }

    void LevelSelectMenu::drawLevelMenu(sf::RenderWindow& window) {
        window.draw(title);
        if (selectedIndex != -1) window.draw(selected);
        for (Button& b : levels) window.draw(b.text);
    }

    int LevelSelectMenu::levelClicked(sf::RenderWindow &window, sf::Event& event) {
        for (size_t i = 0; i < levels.size(); ++i) {
            if (levels[i].isClicked(window, event)) {
                return i;
            }
        }
        return -1;
    }

    void LevelSelectMenu::moveSelectedDown() {
        if (selectedIndex == int(levels.size()) - 1) return;
        selectedIndex += 1;
        selected.move(0,100);
        levels[selectedIndex - 1].text.setFillColor(sf::Color::White);
        levels[selectedIndex].text.setFillColor(sf::Color::Black);
    }    

    void LevelSelectMenu::moveSelectedUp() {
        if (selectedIndex == 0) return;
        selectedIndex -= 1;
        selected.move(0,-100);
        levels[selectedIndex + 1].text.setFillColor(sf::Color::White);
        levels[selectedIndex].text.setFillColor(sf::Color::Black);
    }

    int LevelSelectMenu::playLevelMenu(sf::RenderWindow& window, sf::Event& event) {
        if (!window.pollEvent(event)) getInput = true;
        if (!getInput) return -1;

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::S) moveSelectedDown();
            else if (event.key.code == sf::Keyboard::W) moveSelectedUp();
            else if (event.key.code == sf::Keyboard::Enter) return selectedIndex;
        }
        if (levelClicked(window, event) != -1)
            return selectedIndex;
        return -1;
    }
}