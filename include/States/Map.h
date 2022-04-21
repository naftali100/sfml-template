#pragma once
#ifndef MAP_H
#define MAP_H

#include "Camera.h"
#include "Log.h"
#include "Random.h"
#include "Resources.h"
#include "State.h"
#include "TileMap.h"

class MapState : public State {
public:
    using State::State;

    void init() override {
        // m_camera.setView(m_stateManager.getWin().getView().);

        m_map.setTexture(Textures::Map);
        m_map.setTilesInTextureRow(3);  // maybe skip and do all tile in one line?
        m_map.setTileSize({10, 10});
        m_map.setLayoutWidth(5);
        m_map.generateRandomMap();

        m_camera.setView(sf::Vector2u(10 * 5, 10 * (20 / 5)));
    }

    virtual void handleEvent(const sf::Event& e) override {
        m_camera.handleEvent(e);
    }
    virtual void update(const sf::Time& dt) override {
        ImGui::Text("mouse position: %d, %d", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

        auto layoutSize = m_map.getLayout().size();
        auto tileSize = m_map.getTileSize();
        int layoutWidth = 5;  // temporarily hard coded
        if (ImGui::Button("set view to map size")) {
            m_camera.setView({0, 0, tileSize.x * layoutWidth, tileSize.y * layoutSize / layoutWidth});
        }

        if(ImGui::Button("recreate map")){
            m_map.generateRandomMap();
        }

        if (ImGui::Button("exit")) {
            m_stateManager.popState();
        }
        m_camera.update(dt);
    }
    virtual void draw(sf::RenderTarget& win) const override {
        m_camera.draw(win);
        if(ImGui::Button("zoom at mouse position")){
            // m_camera.zoomViewAt(sf::Mouse::getPosition(), win, 0.9);
        }
        m_map.draw(win);
    }

private:

    TileMap m_map;
    // TileMap m_map{Textures::Map, sf::Vector2f(10, 10), sf::Vector2f(0, 0), std::vector<TileName>(), 100};
    Camera m_camera;
};
#endif