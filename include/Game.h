#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

    void processEvents();
    void update(sf::Time elapsedTime);
    void showStatWin();
    void draw();

private:
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    sf::RenderWindow m_win;
    sf::Font m_font;
    std::map<sf::Keyboard::Key, bool> pressedKeys;
    // StateManager m_stateManager;
};