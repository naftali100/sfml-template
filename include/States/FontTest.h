#pragma once
#ifndef FONTS_H
#define FONTS_H

#include "State.h"
#include "Resources.h"

class FontTest : public State {
public:
    using State::State;

    virtual void handleEvent(const sf::Event&) override{};
    virtual void update(const sf::Time&) override{};
    virtual void draw(sf::RenderTarget& win) const override{
        sf::String s {L"שלום"};
        std::reverse(s.begin(),s.end());
        sf::Text t{s, Resources::getFont(Fonts::Test)};
        t.setPosition(10,10);
        win.draw(t);
    };
};

#endif
