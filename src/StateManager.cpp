#include "StateManager.h"

#include <plog/Log.h>

// #include "state/collisions_state.h"
// #include "state/demo_state.h"
// #include "state/demo_state2.h"
// #include "state/gui_state.h"
// #include "state/resourcess_state.h"

StateManager::StateManager(sf::RenderWindow& win) : m_win(win) {
    LOGV << "state manager constructor - start";
    // registerState<DemoState>(States::Main);
    // registerState<Demo2>(States::Demo2);
    // registerState<ResourcesState>(States::Resources);
    // registerState<ColState>(States::Collision);
    // registerState<GuiState>(States::Gui);

    // TextureHolder::Instance().load(Textures::Player, "textures/player.png");
    LOGV << "state manager constructor - finish";
}

void StateManager::pushState(StatePtr ptr, bool pauseCurrent) {
    if (!pauseCurrent && !m_states.empty()) {
        m_states.pop();
    }
    m_states.push(std::move(ptr));
}

void StateManager::popState() {
    if (!m_states.empty())
        m_states.pop();
}

void StateManager::handleEvent(const sf::Event& e) {
    if (!m_states.empty()) {
        m_states.top()->handleEvent(e);
    }
    else {
        LOGI << "empty states stack";
    }
}

void StateManager::update(const sf::Time& td) {
    // ImGui::Begin("states");
    // if (ImGui::Button("demo state")) {
    //     pushState(createState(States::Main));
    // }
    // if (ImGui::Button("state 2")) {
    //     pushState(createState(States::Demo2));
    // }
    // if (ImGui::Button("resources state")) {
    //     pushState(createState(States::Resources), true);
    // }
    // if (ImGui::Button("collision state")) {
    //     pushState(createState(States::Collision), true);
    // }
    // if (ImGui::Button("gui state")) {
    //     pushState(createState(States::Gui));
    // }

    // if (ImGui::Button("exit current state")) {
    //     popState();
    // }

    // if (ImGui::Button("exit")) {
    //     while (!m_states.empty()) m_states.pop();
    // }

    // ImGui::End();

    if (!m_states.empty()) {
        m_states.top()->update(td);
    }
    else {
        LOGD << "empty states stack";
    }
}

void StateManager::draw(sf::RenderTarget& win) {
    if (!m_states.empty()) {
        m_states.top()->draw(win);
    }
    else {
        LOGD << "empty states stack";
    }
}

bool StateManager::isRunning() const {
    return !m_states.empty();
}

// StatePtr StateManager::createState(States::ID stateID) {
//     auto found = m_factories.find(stateID);
//     assert(found != m_factories.end());

//     return m_factories[stateID]();
// }
