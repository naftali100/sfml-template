#include "doctest/doctest.h"
#include <SFML/Graphics.hpp>
#include "StateManager.h"
// #include "States/MainMenu.h"
#include "States/DemoState.h"

TEST_CASE("test state manager"){
    sf::RenderWindow win(sf::VideoMode(10, 10), "world", sf::Style::Close);

    StateManager sm(win);

    sm.pushState(std::make_unique<DemoState>(sm));
    CHECK(sm.isRunning() == true);

    sm.popState();
    CHECK(sm.isRunning() == false);

    sm.stop();
    CHECK(sm.isRunning() == false);

    win.close();
}
