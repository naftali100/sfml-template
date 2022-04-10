#pragma once
#ifndef state_manager_h
#define state_manager_h

#include <map>
#include <stack>

#include "State.h"

class StateManager {
public:
    StateManager(sf::RenderWindow& win);

    void pushState(StatePtr, bool = false);
    void popState();

    void handleEvent(const sf::Event&);
    void update(const sf::Time& td);
    void draw(sf::RenderTarget&);

    void stop();
    bool isRunning() const;

    // template <typename S>
    // void registerState(States::ID state);

    // StatePtr createState(States::ID);

    sf::RenderWindow& getWin();

    void pause();
    void resume();

private:
    sf::RenderWindow& m_win;
    std::stack<StatePtr> m_states;
    bool m_paused = false;
    // std::map<States::ID, std::function<StatePtr()>> m_factories;
};

// template <typename S>
// void StateManager::registerState(States::ID state) {
//     m_factories[state] = [this]() { return std::make_unique<S>(*this); };
// }

#endif