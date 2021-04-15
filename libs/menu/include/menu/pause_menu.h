//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_PAUSE_MENU_H
#define VOYAGER_PAUSE_MENU_H

#include "menu/i_menu.h"

namespace menu {
    class PauseMenu: public IMenu {
    public:
        void draw(graphics::ICanvas &canvas) override;
        ~PauseMenu() override;
        void update(Event event) override;
    };
}


#endif //VOYAGER_PAUSE_MENU_H
