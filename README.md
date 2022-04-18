# sfml-template
sfml project template with a lot of stuff built in for easy and quick start.

# how to use
- add new state that inherits from State class.
```cpp
class MyState: public State {
public:
    using State::State
    // override State's pure methods
private:
    // all what the state need
    sf::Sprite m_player;
};
```
- set the entry state in game class before the game loop.

# what's in
- states
- animation (using texture atlas)
- easy resource management
- particle system (not the most efficient)
- logging with plog, integrate sfml with plog
- sfml utilities
- imgui

# todo
- quad tree.
- update particle system to use VertexArray and batch rendering (or keep it with drawable?)
- states factories. (?)