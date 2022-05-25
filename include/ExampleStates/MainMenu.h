#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <imgui-SFML.h>
#include <imgui.h>

#include "State.h"
#include "ExampleStates/AnimationState.h"
#include "ExampleStates/DemoState.h"
#include "Log.h"
#include "ExampleStates/Map.h"
#include "ExampleStates/ParticlesState.h"
#include "ExampleStates/XOState.h"
#include "ExampleStates/imguiTest.h"

class MainMenu : public State {
public:
    using State::State;

    virtual void handleEvent(const sf::Event&) override{};
    virtual void update(const sf::Time&) override {
        if (ImGui::Button("Map state")) {
            m_stateManager.pushState(std::make_unique<MapState>(m_stateManager));
        }
        if (ImGui::Button("XO state")) {
            m_stateManager.pushState(std::make_unique<XOState>(m_stateManager));
        }

        if (ImGui::Button("particles state")) {
            m_stateManager.pushState(std::make_unique<ParticlesState>(m_stateManager));
        }

        if (ImGui::Button("Animation state")) {
            m_stateManager.pushState(std::make_unique<AnimationState>(m_stateManager));
        }

        if (ImGui::Button("ImGui test state")) {
            m_stateManager.pushState(std::make_unique<ImGuiTest>(m_stateManager));
        }

        if (ImGui::Button("show demo window")) {
            m_showDemo = true;
        }

        if (m_showDemo) {
            ImGui::ShowDemoWindow(&m_showDemo);
        }

        if (ImGui::Button("exit current state")) {
            m_stateManager.popState();
            return;
        }

        if (ImGui::Button("exit")) {
            m_stateManager.stop();
            return;
        }

        ImGui::Checkbox("pause current state when pushing new state?", &m_pauseOnPush);
        ImGui::Checkbox("show game window", &m_stateManager.m_showImGuiGameWindow);

        LOGD;
    };

    virtual void draw(sf::RenderTarget&) const override{};

private:
    // when pushing new state, pause the current or replace it with new one?
    bool m_pauseOnPush = true;
    bool m_showDemo = false;
};

#endif