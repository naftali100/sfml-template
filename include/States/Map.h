#pragma once
#ifndef MAP_H
#define MAP_H

#include "Camera.h"
#include "Log.h"
#include "Resources.h"
#include "State.h"
#include "TileMap.h"

class MapState : public State {
public:
    using State::State;

    void init() override {
        m_camera.setView(m_stateManager.getWin().getView());

        m_map.setTexture(Textures::Map);
        m_map.setTilesInTextureRow(3);  // maybe skip and do all tile in one line?
        m_map.setTileSize({10, 10});
        m_map.setLayoutWidth(5);
        std::vector<int> vec;
        for (int i = 0; i < 20; i++) { vec.push_back(rand() % 3); }
        m_map.setLayout(vec);
        m_map.renderFullMap();

        m_camera.setView();
    }

    virtual void handleEvent(const sf::Event& e) override {
        m_camera.handleEvent(e);
    }
    virtual void update(const sf::Time& dt) override {
        m_camera.update(dt);
    }
    virtual void draw(sf::RenderTarget& win) const override {
        m_camera.draw(win);
        m_map.draw(win);
    }

private:
    TileMap m_map;
    // TileMap m_map{Textures::Map, sf::Vector2f(10, 10), sf::Vector2f(0, 0), std::vector<TileName>(), 100};
    Camera m_camera;
};
#endif