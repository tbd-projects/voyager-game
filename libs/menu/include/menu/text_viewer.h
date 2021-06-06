//
// Created by volodya on 03.06.2021.
//

#ifndef VOYAGER_TEXT_VIEWER_H
#define VOYAGER_TEXT_VIEWER_H

#include <graphics/i_spite_loader.h>
#include <game/interface.hpp>
#include <game_manager/config.hpp>
#include "vertical_centered_menu.h"

namespace menu {
    class TextViewer : public VerticalCenteredMenu {
    public:
        TextViewer(graphics::ICanvas &canvas, event_controller::IController &controller, graphics::IGraphicsFactory &factory);

        TextViewer(graphics::ICanvas &canvas, event_controller::IController &controller):
                TextViewer(
                        canvas,
                        controller,
                        *game_manager::Config::get_instance().graphics_factory
                ) {};

        ~TextViewer() = default;

        void set_text(graphics::IGraphicsFactory &factory, const std::string &text);

    private:
        static menu::CommandButton _create_line(graphics::IGraphicsFactory &factory,
                                         std::shared_ptr<graphics::Font> &font,
                                         const std::string& line);

    };
}


#endif //VOYAGER_TEXT_VIEWER_H
