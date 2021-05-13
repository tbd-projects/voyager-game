#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class EndGame : public ICommand {
    void execute(GameManager &manager) override {
        manager.end_game();
    }
};

}  // namespace game_manager::command
