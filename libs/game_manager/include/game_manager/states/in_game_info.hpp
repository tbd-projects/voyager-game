#pragma once

#include <menu/game_info.h>
#include <event_controller/i_controller.h>
#include <graphics/i_drawable.h>
#include <game_manager/interface.hpp>


namespace game_manager::states {

class InGameInfo : public IState {
  public:
    InGameInfo() = delete;

    InGameInfo(const InGameInfo &) = delete;

    InGameInfo &operator=(const InGameInfo &) = delete;

    InGameInfo(graphics::ICanvas &canvas,
                event_controller::IController &controller);

    void stop(event_controller::IController &controller) override;

    void resume(event_controller::IController &controller) override;

  private:
    menu::GameInfo _game_info;
};

}  // namespace game_manager::states
