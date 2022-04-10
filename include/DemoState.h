#pragma once
#ifndef DEMO_STATE_H
#define DEMO_STATE_H

#include "SfmlUtil.h"

#include "Config.h"
#include "Particle.h"
#include "State.h"

class DemoState : public State {
public:
    using State::State;
    DemoState(StateManager& sm) : State(sm){
        m_ps.setDissolve(true);
        m_ps.setDissolutionRate(1);
        m_ps.setShape(Shape::CIRCLE);
        m_ps.setParticleSpeed( 80.0f );
        // m_ps.setGravity( 1.0f, 1.0f );
    };

    virtual void handleEvent(const sf::Event& e) override {
        if(e.type == sf::Event::MouseMoved){
            m_ps.setPosition(e.mouseMove.x, e.mouseMove.y);
        }
    }
    virtual void update(const sf::Time&) override {
        m_ps.fuel(50);

        m_ps.remove();
        m_ps.update();
        m_ps.render();
    }
    virtual void draw(sf::RenderTarget& win) const override {
        win.draw(m_ps.getSprite());
    }

private:
    mutable ParticleSystem m_ps{WIN_SIZE_X, WIN_SIZE_Y};
};

#endif