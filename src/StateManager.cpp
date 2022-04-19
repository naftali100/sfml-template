#include "StateManager.h"

#include <plog/Log.h>
#include <imgui.h>

StateManager::StateManager(sf::RenderWindow& win) : m_win(win), swoosh::ActivityController(win) {
    LOGV << "state manager constructor - start";
    // registerState<DemoState>(States::Main);

    LOGV << "state manager constructor - finish";
}

// void StateManager::pushState(StatePtr ptr, bool pauseCurrent) {
//     if (!pauseCurrent && !m_states.empty()) {
//         m_states.pop();
//     }
//     m_states.push(std::move(ptr));
//     // m_states.top()->init();
// }

// void StateManager::popState() {
//     if (!m_states.empty())
//         m_states.pop();
// }

// void StateManager::handleEvent(const sf::Event& e) {
    // getCurrentActivity();
    // if (m_paused)
    //     return;

    // if (!m_states.empty()) {
    //     m_states.top()->handleEvent(e);
    // }
    // else {
    //     LOGI << "empty states stack";
    // }
// }

void StateManager::update(const sf::Time& td) {
    LOGV << "stateManage update - start";

    swoosh::ActivityController::update(td);
    
    if (ImGui::Button("exit current state")) {
        pop();
    }

    if (ImGui::Button("exit")) {

        
    }

    if (m_paused)
        return;
    
    LOGV << "stateManage update - finish";
}

// void StateManager::draw(sf::RenderTarget& win) {
//     if (m_paused)
//         return;

//     if (!m_states.empty()) {
//         swoosh::ActivityController::draw();
//         m_states.top()->draw(win);
//     }
//     else {
//         LOGD << "empty states stack";
//     }
// }

void StateManager::pause() {
    m_paused = true;
};

void StateManager::resume() {
    m_paused = false;
};

void StateManager::stop() {
    m_states = {};
}

bool StateManager::isRunning() const {
    return !m_states.empty();
}

// StatePtr StateManager::createState(States::ID stateID) {
//     auto found = m_factories.find(stateID);
//     assert(found != m_factories.end());

//     return m_factories[stateID]();
// }
