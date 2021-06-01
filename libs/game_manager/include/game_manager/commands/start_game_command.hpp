#pragma once

#include <game_manager/interface.hpp>
#include <game_manager/game_manager.hpp>
#include <game_manager/states/in_game_state.hpp>

namespace game_manager::command {

class RunGame : public ICommand {
  public:
    RunGame() = delete;

    explicit RunGame(size_t id_level)
            : _id_level(id_level) {}

    void execute(GameManager &manager) override {
        size_t out_id_level = _id_level;
        auto creator = [out_id_level](graphics::ICanvas &canvas,
                                  event_controller::IController &controller) {
            return std::make_unique<game_manager::states::InGame>(
                    canvas, controller, out_id_level);
        };

        manager.add_state(creator);
    }

  private:
    size_t _id_level;
};

}  // namespace game_manager::command
