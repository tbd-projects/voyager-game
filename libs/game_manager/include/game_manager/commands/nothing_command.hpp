//
// Модуль Ветошкина Артёма
//

#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class DoNothing : public ICommand {
  public:
    void execute(GameManager &manager) override {
    }
};

}
