#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Log.h"
#include "State.h"

class Ball : public sf::Transformable {
public:
    Ball(){
        m_ball.setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
    }

    void draw(sf::RenderTarget& win) const {
        win.draw(m_ball, getTransform());
    }

private:
    sf::CircleShape m_ball{50};
};


class Paddle : public sf::Transformable {
public:
    Paddle(bool isLeft) : m_isLeft(isLeft) {
        if (m_isLeft) {
            setPosition(5, WIN_SIZE_Y / 2);
        }
        else {
            setPosition(WIN_SIZE_X - 5, WIN_SIZE_Y / 2);
        }
        m_paddle.setSize(sf::Vector2f(10, 200));
        m_paddle.setOrigin(sf::util::getGlobalCenter(m_paddle));
    }

    void move(float Y) {
        if(getPosition().y + Y + 100 <= WIN_SIZE_Y && getPosition().y + Y - 100 >= 0){
            sf::Transformable::move(0, Y);
        }
    }
    void draw(sf::RenderTarget& win) const {
        win.draw(m_paddle, getTransform());
    }

    bool isCollideWithBall(Ball& b){
        return false;
    }

private:
    sf::RectangleShape m_paddle;
    bool m_isLeft;
};

class PaddleState : public State {
public:
    using State::State;
    void init() {}

    virtual void handleEvent(const sf::Event& e) override {
        if (e.type == sf::Event::KeyPressed) {
            m_pressedKeys[e.key.code] = true;
        }
        else if (e.type == sf::Event::KeyReleased) {
            m_pressedKeys[e.key.code] = false;
        }
    }
    virtual void update(const sf::Time& dt) override {
        auto moveSpeed = dt.asMilliseconds();

        if (m_pressedKeys[sf::Keyboard::Up]) {
            m_RPaddle.move(-moveSpeed);
        }
        if (m_pressedKeys[sf::Keyboard::Down]) {
            m_RPaddle.move(moveSpeed);
        }

        if (m_pressedKeys[sf::Keyboard::W]) {
            m_LPaddle.move(-moveSpeed);
        }
        if (m_pressedKeys[sf::Keyboard::S]) {
            m_LPaddle.move(moveSpeed);
        }
    }
    virtual void draw(sf::RenderTarget& win) const override {
        m_LPaddle.draw(win);
        m_RPaddle.draw(win);

        sf::Text t{sf::String("שלום"), Resources::getFont(Fonts::Main)};
        win.draw(t);
    }

private:
    std::map<sf::Keyboard::Key, bool> m_pressedKeys;
    Paddle m_RPaddle{false};
    Paddle m_LPaddle{true};
};

#endif