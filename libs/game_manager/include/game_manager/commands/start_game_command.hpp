#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>

namespace game_manager::command {

class StartGameCommand : public ICommand {
public:
    StartGameCommand() = delete;

    explicit StartGameCommand(size_t id_level)
        : _id_level(id_level) {}

    void execute(GameManager &manager) override {
        manager.start_game(_id_level);
        }

private:
    size_t _id_level;
};

}
