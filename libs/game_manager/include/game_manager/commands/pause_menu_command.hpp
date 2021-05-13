#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class RunPause : public ICommand {
    void execute(GameManager &manager) override {
        manager.pause_game();
    }
};

}  // namespace game_manager::command
