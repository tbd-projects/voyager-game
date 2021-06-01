#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>
#include <game_manager/states/game_over_state.hpp>
#include <game/structs.hpp>

namespace game_manager::command {

class EndGame : public ICommand {
  public:
    EndGame(bool status, const game::level_stat &stats)
            : _status(status)
              , _stats(stats) {}

    void execute(GameManager &manager) override {
        auto creator = [this](graphics::ICanvas &canvas,
                              event_controller::IController &controller) {
            return std::make_unique<game_manager::states::GameOver>(
                    canvas, controller, _status, _stats);
        };
        manager.add_state(creator);
    }

  private:
    bool _status;
    game::level_stat _stats;
};

}  // namespace game_manager::command
