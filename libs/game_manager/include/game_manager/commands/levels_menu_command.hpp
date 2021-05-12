#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class LevelsMenuCommand : public ICommand {
    void execute(GameManager &manager) override {
        manager.open_levels_menu();
    }
};

}
