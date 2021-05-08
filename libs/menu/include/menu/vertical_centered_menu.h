//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_VERTICAL_CENTERED_MENU_H
#define VOYAGER_VERTICAL_CENTERED_MENU_H

#include <vector>
#include "command_button.h"
#include "i_menu.h"

namespace menu {
    class VerticalCenteredMenu: public IMenu{
    private:
        std::vector<CommandButton> _buttons;
        int _active_id = 0;
        int _buttons_height = 50;
        int _buttons_width = 200;
        int _gap = 10;
        void _update_buttons();
        void _draw(graphics::ICanvas *canvas);
    public:
        std::vector<menu::CommandButton> & buttons();

        void update(Event &event) override;

        [[nodiscard]] const CommandButton& get_active_button() const;
        void set_active_id(int i);

        int get_buttons_height() const;

        void set_buttons_height(int height);

        int get_buttons_width() const;

        void set_buttons_width(int width);

        int get_gap() const;

        void set_gap(int gap);
    };
}


#endif //VOYAGER_VERTICAL_CENTERED_MENU_H
