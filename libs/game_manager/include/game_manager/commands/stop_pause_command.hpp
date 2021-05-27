//
// Модуль Ветошкина Артёма
//

#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>
#include <game_manager/states.hpp>

namespace game_manager::command {

class EndPause : public ICommand {
  public:
    void execute(GameManager &manager) override {
        manager.apply_state();
    }
};

}
