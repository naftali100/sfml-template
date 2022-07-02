//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2016 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef SFMLUTIL_H
#define SFMLUTIL_H

/// define CPP_VERSION and has_concepts
#if _MSVC_LANG
#define CPP_VERSION _MSVC_LANG
#elif defined(__linux__) || defined(__MINGW32__)
#define CPP_VERSION __cplusplus
#else
#define CPP_VERSION 201707
#endif

#if __has_include("concepts") && __cpp_concepts <= CPP_VERSION && __cpp_lib_concepts <= CPP_VERSION
#define has_concepts
#endif

/// define concepts

#ifdef has_concepts
#include <concepts>

template <typename T>
concept hasGlobal = requires(T t) {
    t.getGlobalBounds();
};

template <typename T>
concept hasLocal = requires(T t) {
    t.getLocalBounds();
};
#endif

/// utils

namespace sf {
    namespace util {
#ifdef has_concepts
    template <hasLocal T>
    sf::Vector2f getLocalTopLeft(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalTopCenter(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalTopRight(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalCenterLeft(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalCenter(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalCenterRight(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalBottomLeft(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalBottomCenter(const T& object);
    template <hasLocal T>
    sf::Vector2f getLocalBottomRight(const T& object);

    template <hasGlobal T>
    sf::Vector2f getGlobalTopLeft(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalTopCenter(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalTopRight(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalCenterLeft(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalCenter(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalCenterRight(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalBottomLeft(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalBottomCenter(const T& object);
    template <hasGlobal T>
    sf::Vector2f getGlobalBottomRight(const T& object);

    template <hasGlobal T>
    sf::RectangleShape debugDraw(const T& object);

    template <typename T>
    void setOriginToCenter(const T& object);
    
#else   // has_concepts
template <typename T>
inline sf::Vector2f getGlobalCenter(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
}
template <typename T>
inline sf::Vector2f getGlobalTopRight(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width, bounds.top};
}
#endif  // has_concepts
    template <typename T>
    inline sf::Vector2<T> normalize(const sf::Vector2<T>& v) {
        float length = std::sqrt((v.x * v.x) + (v.y * v.y));
        if (length != 0)
            return sf::Vector2<T>(v.x / length, v.y / length);
        else
            return v;
    }

    template <typename T>
    inline float dot(const sf::Vector2<T>& lv, const sf::Vector2<T>& rv) {
        return lv.x * rv.x + lv.y * rv.y;
    }

    template <typename T>
    inline sf::Vector2<T> reflect(const sf::Vector2<T>& velocity, const sf::Vector2<T>& normal) {
        return -2.f * dot(velocity, normal) * normal + velocity;
    }
    }  // namespace util
}  // namespace sf

#ifdef has_concepts
#include "SfmlUtil.tpp"
#endif

#endif  // guard