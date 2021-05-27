//
// Created by volodya on 23.05.2021.
//

#ifndef VOYAGER_CREATE_STANDART_MENU_BUTTON_H
#define VOYAGER_CREATE_STANDART_MENU_BUTTON_H

#include <menu/i_create_menu_button.h>

namespace menu {
    class CreateStandartMenuButton : public ICreateMenuButton {
    public:
        CommandButton create(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
                             std::unique_ptr<event_controller::ICommand> &&command,
                             const std::string &title) override;
    };
}

#endif //VOYAGER_CREATE_STANDART_MENU_BUTTON_H
