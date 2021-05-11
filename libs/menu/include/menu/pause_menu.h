//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "menu/i_menu.h"

namespace menu {
    class PauseMenu: public IMenu {
    public:
        ~PauseMenu() override;
        std::shared_ptr<event_controller::ICommand> update(event_controller::Event &event) override;
    };
}


#endif //VOYAGER_PAUSE_MENU_H
