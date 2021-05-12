#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>
#include <game_manager/states/in_game_state.hpp>

namespace game_manager::command {

class RunGame : public ICommand {
    void execute(GameManager &manager) override {
        auto creator = [](graphics::ICanvas &canvas
                          , event_controller::IController &controller)
                -> std::unique_ptr<game_manager::IState> {
            return std::make_unique<game_manager::states::InGame>(
                    canvas, controller);
        };

        manager.add_state(creator);
    }
};

}  // namespace game_manager::command
