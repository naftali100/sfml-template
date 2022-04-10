#pragma once
#ifndef PARTICLES_STATE_H
#define PARTICLES_STATE_H

#include <plog/Log.h>

#include "Config.h"
#include "ParticleSystem.h"
#include "SfmlUtil.h"
#include "State.h"
#include "resource_identifiers.h"

struct myParticle : public Particle {
    sf::Sprite sprite{TextureHolder::Instance().get(Textures::Player)};
    void init() override {
        sprite.scale(0.1, 0.1);
        sprite.setPosition(m_pos);
    }

    void update() override {
        sprite.setPosition(m_pos);
        sprite.setColor(sf::Color(255, 255, 255, opacity));
    }

    void draw(sf::RenderTarget& r) const override {
        r.draw(sprite);
    }
};

class ParticlesState : public State {
public:
    using State::State;
    ParticlesState(StateManager& sm) : State(sm) {
        m_ps.setDissolve(true);
        m_ps.setDissolutionRate(1);
        m_ps.setShape(Shape::SQUARE);
        m_ps.setParticleSpeed(200.0f);
        // m_ps.setGravity( 1.0f, 1.0f );
    };

    virtual void handleEvent(const sf::Event& e) override {
        if (e.type == sf::Event::MouseMoved) {
            m_ps.setPosition(e.mouseMove.x, e.mouseMove.y);
        }
    }
    virtual void update(const sf::Time&) override {
        m_ps.fuel<myParticle>(200);

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