#pragma once
#ifndef IMGUI_TEST_H
#define IMGUI_TEST_H

#include <imgui-SFML.h>
#include <imgui.h>

#include "Log.h"
#include "Resources.h"
#include "State.h"

class ImGuiTest : public State {
public:
    using State::State;

    void onStart() override {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 12;
        style.FrameRounding = 4;
        style.ScrollbarRounding = 12;
        style.GrabRounding = 12;
    }

    virtual void onEvent(const sf::Event&) override{};
    virtual void onUpdate(const sf::Time&) override {
        if (open) {
            if (ImGui::Begin("hello", &open)) {
                ImGui::Text("hello");
                ImGui::Image(Resources::getTexture(Textures::Player));
            }
            // End should allways be called after begin
            ImGui::End();
        }

        ImGui::Checkbox("toggle window", &open);
        ImGui::ShowDemoWindow();
        // ImGui::SliderScalar("slider")
        // ImGui::ShowAboutWindow();
        // ImGui::ShowFontSelector("hello");
        // ImGui::ShowMetricsWindow();
        // ImGui::ShowStackToolWindow();
        // ImGui::ShowStyleEditor();
        // ImGui::ShowUserGuide();
    };

    virtual void onDraw(sf::RenderTexture& win) override{
        // imGui draw is globally done in Game class
    };

private:
    bool open = true;
};
#endif