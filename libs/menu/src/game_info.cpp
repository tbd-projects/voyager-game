//
// Created by volodya on 03.06.2021.
//

#include <loaders/locale_loader.h>
#include <event_controller/event/keyboard_event.h>
#include <game_manager/commands/main_menu_command.hpp>
#include "../include/menu/game_info.h"

menu::GameInfo::~GameInfo() {

}

menu::GameInfo::GameInfo(graphics::ICanvas &canvas, event_controller::IController &controller,
                         graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader):
                         BackgroundMenuDecorator(canvas, controller, 0, factory, loader),
                         _factory(factory),
                         _loader(loader) {
    LocaleLoader locale;

    set_text(factory, locale.get("info"));
}

std::shared_ptr<event_controller::ICommand> menu::GameInfo::update(event_controller::Event &event) {
    if (event.type == event_controller::keyboard) {
        auto& key = dynamic_cast<event_controller::KeyboardEvent &>(event);
        if (key.key == event_controller::Key::Escape) {
            return std::make_shared<game_manager::command::RunMainMenu>();
        }
    }
    return BackgroundMenuDecorator::update(event);
}

