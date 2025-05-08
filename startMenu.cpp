#include "startMenu.h"
#include "game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Breakout {
    StartMenu::StartMenu()
    : title(), startButton(), quitButton(), selected()
{
    font.loadFromFile("../../Roboto/Roboto-VariableFont_wdth,wght.ttf");

    title.setFont(font);
    title.setString(startMenuTitle);
    title.setCharacterSize(titleFontSize);
    title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
    title.setPosition(titlePos);

    // Start Button
    startButton.rect.setSize(startButtonSize);
    startButton.rect.setOrigin(startButtonSize / 2.f);
    startButton.rect.setPosition(startButtonPos);
    startButton.rect.setFillColor(sf::Color::Transparent);

    startButton.text.setFont(font);
    startButton.text.setString(startButtonText);
    startButton.text.setCharacterSize(textFontSize);
    startButton.text.setFillColor(sf::Color::Black);
    startButton.text.setOrigin(
        startButton.text.getLocalBounds().width / 2.f,
        startButton.text.getLocalBounds().height / 2.f
    );
    startButton.text.setPosition(startButtonPos);

    // Quit Button
    quitButton.rect.setSize(quitButtonSize);
    quitButton.rect.setOrigin(quitButtonSize / 2.f);
    quitButton.rect.setPosition(quitButtonPos);
    quitButton.rect.setFillColor(sf::Color::Transparent);

    quitButton.text.setFont(font);
    quitButton.text.setString(quitButtonText);
    quitButton.text.setCharacterSize(textFontSize);
    quitButton.text.setFillColor(sf::Color::White);
    quitButton.text.setOrigin(
        quitButton.text.getLocalBounds().width / 2.f,
        quitButton.text.getLocalBounds().height / 2.f
    );
    quitButton.text.setPosition(quitButtonPos);

    selected.setSize(sf::Vector2f(screenWidth, startButtonSize.y));
    selected.setOrigin(selected.getSize() / 2.f);
    selected.setPosition(startButtonPos);
    selected.setFillColor(sf::Color::White);
}

    void StartMenu::drawStartMenu(sf::RenderWindow& window) {
        window.draw(title);
        window.draw(selected);
        startButton.drawButton(window);
        quitButton.drawButton(window);
    }

    void StartMenu::moveSelectedDown() {
        if (selectedType != startType) return;

        startButton.text.setFillColor(sf::Color::White);
        quitButton.text.setFillColor(sf::Color::Black);
        selected.setPosition(quitButton.rect.getPosition());
        selectedType = quitType;
    }

    void StartMenu::moveSelectedUp() {
        if (selectedType != quitType) return;

        quitButton.text.setFillColor(sf::Color::White);
        startButton.text.setFillColor(sf::Color::Black);
        selected.setPosition(startButton.rect.getPosition());
        selectedType = startType;
    }

    void StartMenu::chooseSelected() {
        
    }

    int StartMenu::playStartMenu(sf::RenderWindow& window, sf::Event event) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveSelectedDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveSelectedUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (selectedType == startType) return start;
            if (selectedType == quitType) return quit;
        }
        if (startClicked(window, event)) return start;
        if (quitClicked(window, event)) return quit;
        return 1;
    }
}