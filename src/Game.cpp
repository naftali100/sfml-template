#include "Game.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <plog/Log.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Colors.h"
#include "Config.h"
#include "Resources.h"
#include "SfmlUtil.h"
#include "StateManager.h"
#include "States/AnimationState.h"
#include "States/Chat.h"
#include "States/DemoState.h"
#include "States/FontTest.h"
#include "States/PaddleState.h"
#include "States/ParticlesState.h"
#include "States/XOState.h"
#include "States/imguiTest.h"

Game::Game() : m_win(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "World"), m_stateManager(m_win) {}

void Game::loadResources() {
    Resources::loadTexture(Textures::Player, "textures/player.png");
    Resources::loadTexture(Textures::FireAnimationSheet, "textures/fireSheet.png");
    Resources::loadTexture(Textures::Run, "textures/run.png");
    Resources::loadFont(Fonts::Main, FONT_PATH);
    Resources::loadFont(Fonts::Test, "fonts/ttf/KlokanTechNotoSans-Regular.ttf");
    Resources::loadSoundBuffer(SoundEffect::Main, "music/background.ogg");
}

void Game::run() {
    LOGV << "game::run - start";

    // init ImGui window
    bool ImGuiInit = ImGui::SFML::Init(m_win);
    ImGui::GetIO().Fonts->Clear();
    // TODO: check imgui font range and load hebrew range 0x0590 - 0x05FF
    ImGui::GetIO().Fonts->AddFontFromFileTTF("fonts/ttf/KlokanTechNotoSans-Regular.ttf", 25.f);
    bool i = ImGui::SFML::UpdateFontTexture();

    loadResources();

    m_win.setFramerateLimit(FPS);
    m_win.setKeyRepeatEnabled(false);

    // initial state
    m_stateManager.pushState(std::make_unique<ImGuiTest>(m_stateManager));

    sf::Clock clock;
    while (m_stateManager.isRunning()) {
        processEvents();
        sf::Time deltaTime = clock.restart();
        update(deltaTime);
        showStatWin();
        draw();
    }

    ImGui::SFML::Shutdown();

    LOGV << "game::run - finish";
}

void Game::processEvents() {
    sf::Event event;
    while (m_win.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(m_win, event);
        m_stateManager.handleEvent(event);

        switch (event.type) {
            case sf::Event::Resized:
                {  // update the view to the new size of the window
                    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    m_win.setView(sf::View(visibleArea));
                    break;
                }
            case sf::Event::Closed:
                m_win.close();
                m_stateManager.stop();
                break;
            case sf::Event::LostFocus:
                m_stateManager.pause();
                break;
            case sf::Event::GainedFocus:
                m_stateManager.resume();
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    ImGui::SFML::Update(m_win, deltaTime);
    m_stateManager.update(deltaTime);
}

void Game::showStatWin() {
    if (ImGui::Begin("stat window")) {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
    }
    ImGui::End();
}

void Game::draw() {
    LOGV << "game render - start";
    m_win.clear(Colors::Gray);
    m_stateManager.draw(m_win);
    ImGui::SFML::Render(m_win);
    m_win.display();
    LOGV << "game render - finish";
}
