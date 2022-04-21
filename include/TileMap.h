#pragma once
#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Log.h"

enum TileName
{
    Land,
    Dirt,
    Water
};

class TileMap {
public:
    TileMap() = default;
    // TileMap(Textures::ID texture, const sf::Vector2f& tileSize, const sf::Vector2f& TileOffset,
    //         const std::vector<TileName>& layout, const int layoutWidth) {
    //     renderFullMap();
    // }
    void setTexture(Textures::ID texture) {
        m_textureID = texture;
    }
    void setTileSize(const sf::Vector2f& tileSize) {
        m_tileSize = tileSize;
    }
    void setOffset(const sf::Vector2f& offset) {}

    void setLayout(const std::vector<TileName>& layout) {
        m_layout.reserve(layout.size());
        for (int i : layout) { m_layout.emplace_back(i); }
    }
    void setLayout(const std::vector<int>& layout) {
        m_layout = layout;
    }
    // or, all tiles in one row?
    void setTilesInTextureRow(int) {}
    void setLayoutWidth(int w) {
        m_layoutWidth = w;
    }
    void setView(const sf::View&) {}
    void setView(const sf::Vector2u& view) {}
    sf::Sprite getTile(TileName) {
        // m_sprite.setTextureRect();
        return m_sprite;
    }

    void renderFullMap() {
        m_fullMap.create(m_layoutWidth * m_tileSize.x, m_layout.size() / m_layoutWidth * m_tileSize.y);
        sf::Vector2f startPoint, drawPos;
        startPoint = drawPos = {0, 0};
        int counter = 0;
        for (int tileID : m_layout) {
            // next line
            if (counter % m_layoutWidth == 0) {
                drawPos.x = startPoint.x;
                drawPos.y += m_tileSize.y;
            }
            // draw
            // get the tile in the texture: go tileSize the amount from the counter to the end of "line" of tiles in the
            // texture
            auto rec = sf::IntRect(sf::Vector2i(m_tileSize.x * tileID, 0), (sf::Vector2i)m_tileSize);
            LOGI << rec;
            sf::Sprite s{Resources::getTexture(m_textureID), rec};
            s.setPosition(drawPos);
            m_fullMap.draw(s);

            // move to next tile position
            drawPos.x += m_tileSize.x;
            counter++;
        }
        m_fullMap.display();
    }

    void draw(sf::RenderTarget& win) const {
        sf::Sprite s{m_fullMap.getTexture()};
        // s.setTextureRect;
        win.draw(s);
    }

private:
    Textures::ID m_textureID;
    int m_layoutWidth;
    sf::Sprite m_sprite;
    std::vector<int> m_layout;
    // sf::Texture& m_mapTexture;
    sf::RenderTexture m_fullMap;  // re-render only when there is a change
    sf::View m_camera;
    sf::Vector2f m_tileSize;
};

#endif