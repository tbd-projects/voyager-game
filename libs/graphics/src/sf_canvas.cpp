//
// Created by volodya on 06.05.2021.
//
#include <SFML/Graphics/RenderWindow.hpp>
#include "graphics/sf_canvas.h"

namespace graphics {
    SfCanvas::SfCanvas() : window(
            ::sf::RenderWindow(
                    ::sf::VideoMode::getDesktopMode(),
                    "MyApp",
                    sf::Style::Fullscreen
            )
    ) {}

    int SfCanvas::get_width() {
        return static_cast<int>(window.getSize().x);
    }

    int SfCanvas::get_height() {
        return static_cast<int>(window.getSize().y);
    }

    void SfCanvas::clear() {
        window.clear();
    }

    void SfCanvas::apply() {
        window.display();
    }

    SfCanvas::~SfCanvas() {
        window.close();
    }

    ::sf::RenderWindow &SfCanvas::get_sf_window() {
        return window;
    }

    SfCanvas::SfCanvas(int width, int height, bool is_full) : window(
            ::sf::RenderWindow(
                    ::sf::VideoMode(width, height),
                    "MyApp",
                    is_full ? sf::Style::Fullscreen : sf::Style::Default
            )
    ) {}
}