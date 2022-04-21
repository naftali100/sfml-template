#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <imgui.h>

#include <SFML/Graphics.hpp>

#include "Log.h"
#include "State.h"

class Camera {
public:
    void setView(const sf::View& view) {
        m_view = view;
    }
    void setView(const sf::Vector2u& size) {
        m_view = sf::View(sf::FloatRect(0.0f, 0.0f, (float)size.x, (float)size.y));
    }
    void setView(const sf::FloatRect& rect) {
        m_view = sf::View(rect);
    }

    virtual void handleEvent(const sf::Event& e) {
        switch (e.type) {
            case sf::Event::Resized:
                m_view.setSize(e.size.width, e.size.height);
                break;
            case sf::Event::MouseWheelScrolled:
                if (e.mouseWheelScroll.delta > 0) {
                    // zoomViewAt({ e.mouseWheelScroll.x, e.mouseWheelScroll.y }, window, (1.f / zoomAmount));
                }
                else if (e.mouseWheelScroll.delta < 0) {
                    // zoomViewAt({ e.mouseWheelScroll.x, e.mouseWheelScroll.y }, window, zoomAmount);
                }
                break;
        }
    }

    virtual void update(const sf::Time& dt) {
        float cameraSpeed = 100 * dt.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            m_view.move(0, -cameraSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            m_view.move(0, cameraSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_view.move(-cameraSpeed, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            m_view.move(cameraSpeed, 0);
        }

        float zoomSpeed = 1 * dt.asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            m_view.zoom(1 - zoomSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            m_view.zoom(1 + zoomSpeed);
        }

        if (ImGui::Button("center to 0,0")) {
            m_view.setCenter(0, 0);
        }

        static float fx = 0;
        static float fy = 0;
        ImGui::SliderFloat("viewport x", &fx, 0, 1, NULL);
        ImGui::SliderFloat("viewport y", &fy, 0, 1, NULL);
        if (ImGui::Button("set view port")) {
            m_view.setViewport(sf::FloatRect{0, 0, fx, fy});
        }

        if (ImGui::Button("print viewport")) {
            LOGI << m_view.getViewport();
        }

        if (ImGui::Button("print view center")) {
            LOGI << m_view.getCenter();
        }

        if (ImGui::Button("print view size")) {
            LOGI << m_view.getSize();
        }
    }

    // set the view to window
    virtual void draw(sf::RenderTarget& win) const {
        // if (ImGui::Button("reset view to window size")) {
            // auto rec = sf::FloatRect{0, 0, win.getSize().x, win.getSize().y};
            // m_view = sf::View(rec);
        // }
        win.setView(m_view);
    }

    void zoomViewAt(sf::Vector2i pixel, sf::RenderTarget& window, float zoom) {
        const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
        sf::View view{window.getView()};
        view.zoom(zoom);
        window.setView(view);
        const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
        const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
        view.move(offsetCoords);
        window.setView(view);
        m_view = window.getView();
    }

private:
    mutable sf::View m_view;
};

#endif