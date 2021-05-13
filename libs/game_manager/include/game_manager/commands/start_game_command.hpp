#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class StartGameCommand : public ICommand {
  public:
    StartGameCommand() = delete;

    StartGameCommand(size_t id_index)
        : _id_index(id_index) {}

    void execute(GameManager &manager) override {
        manager.start_game(_id_index);
    }

  private:
    size_t _id_index;
};

}
