#pragma once
#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "Animation.h"
#include "Log.h"
#include "State.h"
#include "StateManager.h"
#include "SfmlUtil.h"

auto testing_grid() {
    int rows = 1200, cols = 800;
    int numLines = rows + cols - 2;
    sf::VertexArray grid = sf::VertexArray(sf::Lines, 2 * (numLines));

    float rowH = 960;
    float colW = 640;
    auto size = sf::Vector2f(rowH * rows, colW * cols);

    // row separators
    for (int i = 0; i < rows - 1; i++) {
        int r = i + 1;
        float rowY = rowH * r;
        if ((i + 1) % 10 == 0)
            continue;
        grid[i * 2].position = {0, rowY};
        grid[i * 2 + 1].position = {size.x, rowY};
    }
    // column separators
    for (int i = rows - 1; i < numLines; i++) {
        int c = i - rows + 2;
        float colX = colW * c;
        if ((i + 2) % 10 == 0)

            continue;
        grid[i * 2].position = {colX, 0};
        grid[i * 2 + 1].position = {colX, size.y};
    }
    return grid;
    // window.draw(grid);
}

class AnimationState : public State {
public:
    // using State::State;
    AnimationState(StateManager& sm) : State(sm) {
        m_sprite.scale(2, 2);
        sf::Vector2u textureSize = m_sprite.getTexture()->getSize();

        int textureRows = 8;
        int textureCols = 8;

        int FrameXSize = textureSize.x / textureRows;
        int FrameYSize = textureSize.y / textureCols;


        for(int i = 0; i < textureRows; i++){
            for(int j = 0; j < textureCols; j++){
                animation.addFrame({sf::IntRect(i * FrameXSize, j * FrameYSize, FrameXSize, FrameYSize), 0.1});
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
    mutable sf::Sprite m_sprite{TextureHolder::Instance().get(Textures::Run)};
    Animation animation{m_sprite};
};

#endif