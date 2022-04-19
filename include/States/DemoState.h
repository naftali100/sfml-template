#pragma once
#ifndef DEMO_STATE_H
#define DEMO_STATE_H

#include "State.h"
#include "States/Player.h"
#include "Command.h"

#include <plog/Log.h>

class DemoState: public State{
public:
    using State::State;
    virtual void onEvent(const sf::Event& e) override{
        if(e.type == sf::Event::MouseButtonReleased){
            auto snap = m_player.createSnapshot();
            m_player.nextYear();
            LOGI << "age before undo " << m_player.getAge();
            m_commands.push(snap);
            undoMovements();
            LOGI << "age after undo " << m_player.getAge();
        }
        // if undo button pressed
    };
private:
    void undoMovements(){
        m_commands.top().restore();
    }
    Player m_player;
    std::stack<Momento2> m_commands;
    // buttom undo
};
#endif