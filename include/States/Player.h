#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Log.h"
#include "Momento.h"

class Player {
public:
    Player() {
        m_age = 0;
    }

    void nextYear() {
        m_age++;
    }

    auto createSnapshot() {
        return Momento2([age = m_age, this]() {
            this->m_age = age;
        });
    }

    void restoreFromSnap(Momento<Player> m) {
        m_age = m.getObject().m_age;
    }

    int getAge() {
        return m_age;
    }

private:
    friend Momento<Player>;
    int m_age;
};

#endif