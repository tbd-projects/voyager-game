#include <memory>
#include <functional>
#include <utility>

#include <debug/exception.hpp>
#include <menu/pause_menu.h>
#include <menu/main_menu.h>

#include "game_manager.hpp"
#include "config.hpp"

namespace game_manager {

GameManager::GameManager(graphics::ICanvas &canvas
                         , event_controller::IEventable &eventable)
        : _controller(*this, eventable)
        , _canvas(canvas) {}

void GameManager::run() {
    _controller.run();
}

void GameManager::stash_state(const func_create_state& creator_state) {
    stash_state();
    add_state(creator_state);
}

void GameManager::stash_state() {
    _stash_state = std::move(_current_state);
    _stash_state->stop(_controller);
    _current_state = nullptr;
}

void GameManager::apply_state() {
    if (_stash_state == nullptr) {
        throw debug::ARG_UNEXPECTED_CALL_ERROR("try unstash empty stash state");
    }

    _current_state = std::move(_stash_state);
    _stash_state = nullptr;
    _current_state->contine(_controller);
}

void GameManager::add_state(const func_create_state& creator_state) {
    _current_state = creator_state(_canvas, _controller);
}

void GameManager::end_run() {
    _controller.stop();
}

void GameManager::free_stash() {
    if (_stash_state != nullptr) {
        _stash_state = nullptr;
    }
}

}  // namespace game_manager
