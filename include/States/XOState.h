#pragma once
#ifndef OXSTATE_H
#define OXSTATE_H

#include <SFML/Graphics.hpp>
#include <array>

#include "Log.h"
#include "Resources.h"
#include "State.h"
#include "Colors.h"

enum peace
{
    X,
    O,
    Empty
};

char peaceToChar(peace p) {
    switch (p) {
        case X:
            return 'x';
        case O:
            return 'O';
        case Empty:
            return ' ';
    }
    return ' ';
}

// ===========================
// Tile - one square in board
// ===========================
class Tile : public sf::Transformable {
public:
    Tile(sf::Color c) : m_color(c) {}

    void setPeace(peace p) {
        m_peace = p;
    }

    peace getPeace() {
        return m_peace;
    }

    sf::FloatRect getGlobalBounds() const {
        return sf::FloatRect{getPosition(), m_size};
    }

    void draw(sf::RenderTarget& win) const {
        sf::RectangleShape tile{m_size};
        tile.setPosition(getPosition());
        tile.setFillColor(m_color);
        win.draw(tile);

        sf::Text p;
        p.setFont(Resources::getFont(Fonts::Main));
        p.setString(peaceToChar(m_peace));
        p.setOrigin(sf::util::getGlobalCenter(p));
        p.setPosition(sf::util::getGlobalCenter(tile));
        p.setFillColor(sf::Color::Green);
        win.draw(p);
    }

private:
    peace m_peace = Empty;
    sf::Color m_color;
    sf::Vector2f m_size = {50, 50};
};

class XOState : public State {
public:
    using State::State;

    virtual void onStart() override {
        sf::Vector2f startPos{0, 0};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m_board[i][j].setPosition(startPos);
                startPos = sf::util::getGlobalTopRight(m_board[i][j]);
            }
            startPos.y += 50;
            startPos.x = 0;
        }
        setBGColor(Colors::Gray);
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

    virtual void onEvent(const sf::Event& e) override {
        if (e.type == sf::Event::MouseButtonReleased) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (m_board[i][j].getGlobalBounds().contains(sf::Vector2f(e.mouseButton.x, e.mouseButton.y))) {
                        if (m_board[i][j].getPeace() == Empty) {
                            m_board[i][j].setPeace(m_turn);
                            if (checkIfWon() || checkIfTie()) {
                                resetGame();
                            }
                            else {
                                switchTurn();
                            }
                        }
                    }
                }
            }
        }
    }
    virtual void onUpdate(const sf::Time&) override {
        ImGui::Text("X won %d time/s\nO won %d time/s", m_XWins, m_OWins);
    }
    virtual void onDraw(sf::RenderTexture& win) override {
        static bool once = true;
        LOGI_IF(once);
        once = false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) { m_board[i][j].draw(win); }
        }
    }

    void switchTurn() {
        if (m_turn == X) {
            m_turn = O;
        }
        else {
            m_turn = X;
        }
    }

    bool checkIfRowIsSame(int row) {
        auto t = m_board[row][0].getPeace();
        return m_board[row][1].getPeace() == t && m_board[row][2].getPeace() == t && t != Empty;
    }

    bool checkIfColIsSame(int col) {
        auto t = m_board[0][col].getPeace();
        return m_board[1][col].getPeace() == t && m_board[2][col].getPeace() == t && t != Empty;
    }

    bool checkIfCrossIsSame() {
        // TODO: not working. complete this
        peace t = m_turn;
        bool isCross = true;
        for (int i = 0; i < 3; i++) {
            if (m_board[i][i].getPeace() != t || m_board[i][i].getPeace() == Empty) {
                isCross = false;
                break;
            }
        }
        if (!isCross)
            return false;

        for (int i = 0; i < 3; i++) {
            if (m_board[i][2 - i].getPeace() != t || m_board[i][2 - i].getPeace() == Empty) {
                isCross = false;
                break;
            }
        }
        return isCross;
    }

    bool checkIfWon() {
        for (int i = 0; i < 3; i++) {
            if (checkIfColIsSame(i) || checkIfRowIsSame(i) || checkIfCrossIsSame()) {
                m_turn == X ? m_XWins++ : m_OWins++;
                LOGI << checkIfColIsSame(i);
                LOGI << checkIfRowIsSame(i);
                LOGI << checkIfCrossIsSame();
                LOGI << peaceToChar(m_turn) << " win";
                return true;
            }
        }
        return false;
    }

    bool checkIfTie() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (m_board[i][j].getPeace() == Empty)
                    return false;
            }
        }
        return true;
    }

    void resetGame() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) { m_board[i][j].setPeace(Empty); }
        }
    }

private:
    // board - made of 3x3 tiles
    std::array<std::array<Tile, 3>, 3> m_board = {
        std::array<Tile, 3>{sf::Color::Black, sf::Color::White, sf::Color::Black},
        {sf::Color::White, sf::Color::Black, sf::Color::White},
        {sf::Color::Black, sf::Color::White, sf::Color::Black}};

    peace m_turn = X;
    int m_XWins = 0;
    int m_OWins = 0;
};
#endif