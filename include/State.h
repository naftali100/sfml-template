#pragma once
#ifndef state_h
#define state_h

#include <SFML/Graphics.hpp>
#include <memory>

#include "Swoosh/Activity.h"

class StateManager;

// template for states
class State : public swoosh::Activity {
public:
    State(swoosh::ActivityController& ac, StateManager& sm) : m_stateManager(sm), Activity(&ac){};
    State(StateManager& sm) : m_stateManager(sm), Activity((swoosh::ActivityController*)&sm){};
    /* for state init when `using State::State`. called by stateManager */
    // virtual void init(){};
    // virtual void handleEvent(const sf::Event&) = 0;
    // virtual void update(const sf::Time&) = 0;
    // virtual void draw(sf::RenderTarget&) const = 0;

    virtual void onStart(){};
    virtual void onLeave(){};
    virtual void onExit(){};
    virtual void onEnter(){};
    virtual void onResume(){};
    virtual void onEnd(){};
    virtual void onEvent(const sf::Event&){};
    virtual void onUpdate(const sf::Time& elapsed){};
    // !should be const!
    virtual void onDraw(sf::RenderTexture& surface) override {};

    virtual ~State() = default;

protected:
    StateManager& m_stateManager;
};

typedef std::unique_ptr<State> StatePtr;

#endif