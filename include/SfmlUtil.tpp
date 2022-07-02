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

namespace sf {
namespace util {

template <hasLocal T>
sf::Vector2f getLocalTopLeft(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left, bounds.top};
}
template <hasLocal T>
sf::Vector2f getLocalTopCenter(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top};
}
template <hasLocal T>
sf::Vector2f getLocalTopRight(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width, bounds.top};
}
template <hasLocal T>
sf::Vector2f getLocalCenterLeft(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left, bounds.top + bounds.height / 2.f};
}
template <hasLocal T>
sf::Vector2f getLocalCenter(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
}
template <hasLocal T>
sf::Vector2f getLocalCenterRight(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width, bounds.top + bounds.height / 2.f};
}
template <hasLocal T>
sf::Vector2f getLocalBottomLeft(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left, bounds.top + bounds.height};
}
template <hasLocal T>
sf::Vector2f getLocalBottomCenter(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height};
}
template <hasLocal T>
sf::Vector2f getLocalBottomRight(const T& object) {
    const sf::FloatRect bounds{object.getLocalBounds()};
    return {bounds.left + bounds.width, bounds.top + bounds.height};
}

template <hasGlobal T>
sf::Vector2f getGlobalTopLeft(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left, bounds.top};
}
template <hasGlobal T>
sf::Vector2f getGlobalTopCenter(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top};
}
template <hasGlobal T>
sf::Vector2f getGlobalTopRight(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width, bounds.top};
}
template <hasGlobal T>
sf::Vector2f getGlobalCenterLeft(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left, bounds.top + bounds.height / 2.f};
}
template <hasGlobal T>
sf::Vector2f getGlobalCenter(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
}
template <hasGlobal T>
sf::Vector2f getGlobalCenterRight(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width, bounds.top + bounds.height / 2.f};
}
template <hasGlobal T>
sf::Vector2f getGlobalBottomLeft(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left, bounds.top + bounds.height};
}
template <hasGlobal T>
sf::Vector2f getGlobalBottomCenter(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height};
}
template <hasGlobal T>
sf::Vector2f getGlobalBottomRight(const T& object) {
    const sf::FloatRect bounds{object.getGlobalBounds()};
    return {bounds.left + bounds.width, bounds.top + bounds.height};
}

template <hasGlobal T>
sf::RectangleShape debugDraw(const T& object) {
    sf::RectangleShape bound;
    bound.setSize({object.getGlobalBounds().width, object.getGlobalBounds().height});
    bound.setPosition(object.getGlobalBounds().left, object.getGlobalBounds().top);
    bound.setFillColor(sf::Color::Transparent);
    bound.setOutlineColor(sf::Color::Red);
    bound.setOutlineThickness(2);

    return bound;
}

template <typename T>
void setOriginToCenter(const T& object) {
    object.setOrigin(getGlobalCenter(object));
}

}  // namespace util
}  // namespace sf
