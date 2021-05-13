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
        , _game(nullptr)
        , _canvas(canvas)
        , _menu(nullptr)
        , _on_pause(false)
        , _in_game(false) {
//    _game.stop_game(_controller);
}

void GameManager::start_game(size_t id_level) {
    if (_in_game) {
        throw debug::ARG_UNEXPECTED_CALL_ERROR("run game, when it's runned");
    }

    _in_game = true;

    _menu = nullptr;
    _game = std::make_unique<game::Game>(_controller, _canvas);
    _game->start_game(id_level);
}

void GameManager::pause_game() {
    if (!_in_game) {
        throw debug::ARG_UNEXPECTED_CALL_ERROR("start pause was called "
                                               "without run game");
    }

    if (!_on_pause) {
//        _menu = std::make_unique<menu::PauseMenu>();
//        _game.stop_game(_controller);
    }
}

void GameManager::end_game() {
    _game = nullptr;
    open_main_menu();
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

void GameManager::run() {
    _controller.run();
}

void GameManager::exit() {
    _controller.stop();
}

void GameManager::end_pause() {
    if (!_in_game || !_on_pause) {
        throw debug::ARG_UNEXPECTED_CALL_ERROR("end_pause, when it wasn't used,"
                                               " or when not exisist game");
    }

//    _game.continue_game(_controller);
    _menu = nullptr;
}

    void GameManager::open_levels_menu() {

    }

}  // namespace game_manager
