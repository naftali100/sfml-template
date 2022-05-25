#pragma once
#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "Animation.h"
#include "Log.h"
#include "State.h"
#include "StateManager.h"
#include "Resources.h"

class AnimationState : public State {
public:
    AnimationState(StateManager& sm) : State(sm) {
        m_sprite.scale(0.5, 0.5);
        sf::Vector2u textureSize = m_sprite.getTexture()->getSize();

        int textureRows = 3;
        int textureCols = 4;

        int FrameXSize = textureSize.x / textureCols;
        int FrameYSize = textureSize.y / textureRows;

        for (int i = 0; i < textureRows; i++) {
            for (int j = 0; j < textureCols; j++) {
                animation.addFrame({sf::IntRect(i * FrameXSize, j * FrameYSize, FrameXSize, FrameYSize), 0.3});
            }
        }
    }

    virtual void handleEvent(const sf::Event&) override {}
    virtual void update(const sf::Time& dt) override {
        animation.update(dt.asSeconds());
    };
    virtual void draw(sf::RenderTarget& win) const override {
        win.draw(m_sprite);
    }

private:
    sf::Sprite m_sprite{TextureHolder::get(Textures::Run)};
    Animation animation{m_sprite};
};

#endif