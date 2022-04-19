#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <imgui-SFML.h>
#include <imgui.h>

#include "State.h"
#include "States/AnimationState.h"
#include "States/DemoState.h"
#include "Log.h"
#include "States/ParticlesState.h"
#include "States/XOState.h"
#include "States/imguiTest.h"

#include <Swoosh/ActivityController.h>
#include <Swoosh/ActionList.h>
#include <Segues/ZoomOut.h>
#include <Segues/BlackWashFade.h>
#include <Segues/Dream.h>
#include <Segues/BlurFadeIn.h>

using namespace swoosh;
using namespace swoosh::types;

class MainMenu : public State {
public:
    using State::State;
    void onStart() override {
        setBGColor(sf::Color::Green);
    }

    virtual void onLeave(){
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };
    virtual void onExit(){
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };
    virtual void onEnter(){
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };
    virtual void onResume(){
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };
    virtual void onEnd(){
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };

    // virtual void handleEvent(const sf::Event&) override{};
    virtual void onUpdate(const sf::Time&) override {
        if (ImGui::Button("XO state")) {
            m_stateManager.push<segue<BlurFadeIn>::to<XOState>>(m_stateManager);
            // m_stateManager.pushState(std::make_unique<XOState>(m_stateManager), m_pauseOnPush);
        }

        if (ImGui::Button("particles state")) {
            m_stateManager.push<segue<DreamCustom<50>, sec<3>>::to<ParticlesState>>(m_stateManager);
            // m_stateManager.pushState(std::make_unique<ParticlesState>(m_stateManager), m_pauseOnPush);
        }

        if (ImGui::Button("Animation state")) {
            m_stateManager.push<segue<Dream, sec<3>>::to<AnimationState>>(m_stateManager);
            // m_stateManager.pushState(std::make_unique<AnimationState>(m_stateManager), m_pauseOnPush);
        }

        if(ImGui::Button("imgui state")){
            m_stateManager.push<segue<Dream, sec<3>>::to<ImGuiTest>>(m_stateManager);
            // m_stateManager.pushState(std::make_unique<ImGuiTest>(m_stateManager), m_pauseOnPush);
        }

        ImGui::Checkbox("pause current state when pushing new state?", &m_pauseOnPush);
    };

    virtual void onDraw(sf::RenderTexture&) override{
        static bool once = true;
        LOGI_IF(once);
        once = false;
    };

private:
    // when pushing new state, pause the current or replace it with new one?
    bool m_pauseOnPush = true;
};

#endif