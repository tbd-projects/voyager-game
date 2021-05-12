#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>
#include <game_manager/states.hpp>

namespace game_manager::command {

class Exit : public ICommand {
    void execute(GameManager &manager) override {
        manager.end_run();
    }
};

}
