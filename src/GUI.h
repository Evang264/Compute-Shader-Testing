#pragma once

#include <SFML/Window/Window.hpp>

namespace GUI
{

    void init(sf::Window* window);

    void begin_frame();

    void shutdown();
    void render();

    void event(const sf::Window& window, sf::Event& e);

} // namespace GUI