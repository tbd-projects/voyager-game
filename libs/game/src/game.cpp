#include <stdexcept>
#include "game.hpp"

Map::Map(CreatorLevel *level) {

}

Map::Map(const Map &map) {
}

bool Map::update() {
    return false;
}

void Map::check_all_collision() {

}

Progress::Progress(ProgressLoader *loader) {
    if (!loader) {
        throw std::invalid_argument("ProgressLoader ptr invalid");
    }
}

Progress::Progress(const progress_t &progress) {
    this->_progress = progress;
}

Progress &Progress::operator=(const Progress &progress) {
    if (&progress != this) {
        Progress tmp(progress);
        std::swap(this->_progress, tmp._progress);
    }
    return *this;
}

progress_t &Progress::get_progress() {
    return this->_progress;
}

progress_t &Progress::set_progress(progress_t &progress) {
    this->_progress = progress;
    return progress;
}

// Game

Game::Game(IController *controller) {

}

Game::~Game() {

}

void Game::update() {

}

bool Game::start_game() {
    return false;
}

bool Game::stop_game() {
    return false;
}

