#pragma once
#ifndef PARTICLES_STATE_H
#define PARTICLES_STATE_H

#include "Config.h"
#include "ParticleSystem.h"
#include "SfmlUtil.h"
#include "State.h"
#include "Resources.h"


class ParticlesState : public State {
public:
    using State::State;
    void init() override {
        m_ps.setDissolutionRate(1);
        m_ps.setShape(Shape::CIRCLE);
        m_ps.setParticleSpeed(50.0f);
        m_ps.setGravity( 0.f, -1.0f );
        m_ps.setPosition(500,500);
    };

    virtual void handleEvent(const sf::Event& e) override {
        // if (e.type == sf::Event::MouseMoved) {
        //     m_ps.setPosition(e.mouseMove.x, e.mouseMove.y);
        // }
    }
    virtual void update(const sf::Time& dt) override {
        static int deffer = 0;
        deffer++;
        if(deffer % 5 == 0){
            m_ps.addParticles<BaseSpriteParticle>(3);
        }
        m_ps.update(dt);
    }
    virtual void draw(sf::RenderTarget& win) const override {
        m_ps.draw(win);
    }

private:
    ParticleSystem m_ps;
};

#endif