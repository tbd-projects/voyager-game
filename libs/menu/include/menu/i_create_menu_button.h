//
// Created by volodya on 23.05.2021.
//

#ifndef VOYAGER_I_CREATE_MENU_BUTTON_H
#define VOYAGER_I_CREATE_MENU_BUTTON_H

#include <graphics/i_graphics_factory.h>
#include "command_button.h"

namespace menu {
    class ICreateMenuButton {
    public:
        virtual menu::CommandButton
        create(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
               std::unique_ptr<event_controller::ICommand> &&command, const std::string &title) = 0;
    };
}

#endif //VOYAGER_I_CREATE_MENU_BUTTON_H
