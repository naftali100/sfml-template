#include "StateManager.h"

#include "ExampleStates/DemoState.h"
#include "doctest/doctest.h"

sf::RenderWindow win;

TEST_CASE("test state manager") {
    StateManager sm(win);

    sm.pushState(std::make_unique<DemoState>(sm));

    CHECK(sm.isRunning() == true);

    SUBCASE("pop state") {
        sm.popState();
        CHECK(sm.isRunning() == false);
    }

    SUBCASE("stop") {
        sm.stop();
        CHECK(sm.isRunning() == false);
    }

    win.close();
}
