#include "Game.h"

#include <plog/Log.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

#include "Config.h"
#include "SfmlUtil.h"

Game::Game() : m_win(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "World") {
    // FontHolder::Instance().load(Fonts::Main, FONT_PATH);
}

void Game::run() {
    LOGV << "game::run - start";

    m_win.setFramerateLimit(FPS);
    // m_win.setKeyRepeatEnabled(false);

    bool once = true;

    // m_stateManager.setWin(m_win);
    // m_stateManager.pushState(std::make_unique<ColState>(m_stateManager));

    sf::Clock clock;
    while (m_win.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        showStatWin();
        draw();
    }

    LOGV << "game::run - finish";
}

void Game::processEvents() {
    sf::Event event;
    while (m_win.pollEvent(event)) {
        // m_stateManager.handleEvent(event);

        switch (event.type) {
            case sf::Event::Resized:
                {  // update the view to the new size of the window
                    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    m_win.setView(sf::View(visibleArea));
                    break;
                }
            case sf::Event::Closed:
                m_win.close();
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    // m_stateManager.update(deltaTime);
}

void Game::showStatWin() {
    // if (ImGui::Begin("stat window")) {
    //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
    //                 ImGui::GetIO().Framerate);
    // }
    // ImGui::End();
}

void Game::draw() {
    LOGV << "game render - start";
    m_win.clear();
    // m_stateManager.draw(m_win);
    // ImGui::SFML::Render(m_win);
    m_win.display();
    LOGV << "game render - finish";
}
