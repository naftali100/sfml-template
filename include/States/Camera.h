#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

#include "Log.h"
#include "State.h"

class Camera {
public:
    void setView(const sf::View& v) {
        m_view = v;
    }
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
            ImGui::LogText("hello");
        }

        static bool showDemo = false;
        if (ImGui::Button("show demo win")) {
            showDemo = true;
        }

        if (showDemo) {
            ImGui::ShowDemoWindow(&showDemo);
        }
    }

    // set the view to window
    virtual void draw(sf::RenderTarget& win) const {
        win.setView(m_view);
    }

private:
    sf::View m_view;
};

#endif