#include <debug/exception.hpp>
#include <memory>
#include <menu/pause_menu.h>
#include <menu/main_menu.h>

#include "game_manager.hpp"
#include "config.hpp"

namespace game_manager {

GameManager::GameManager(graphics::ICanvas &canvas
                         , event_controller::IEventable &eventable)
        : _controller(*this, eventable)
        , _game(&_controller)
        , _canvas(canvas)
        , _menu(nullptr)
        , _on_pause(false)
        , _in_game(false) {}

void GameManager::start_game() {
}

void GameManager::pause_game() {
    if (!_in_game) {
        throw debug::ARG_UNEXPECTED_CALL_ERROR("start pause was called "
                                               "without run game");
    }

    if (!_on_pause) {
        _menu = std::make_unique<menu::PauseMenu>();
    }
}

void GameManager::end_game() {
}

void GameManager::open_main_menu() {
    if (_in_game) {
        _in_game = false;
    }

    const auto& config = Config::get_instance();
    _menu = std::make_unique<menu::MainMenu>(_canvas, _controller
                                             , *config.graphics_factory
                                             , *config.sprite_loader);
}

void GameManager::open_levels_menu() {
}

void GameManager::run() {
    _controller.run();
}

}  // namespace game_manager
