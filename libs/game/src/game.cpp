#include <stdexcept>
#include "game.hpp"

Map::Map(CreatorLevel *level) {

}

Map::Map(const Map &map) {
}

Map::Map() {

}

bool Map::update() {
    return false;
}

void Map::check_all_collision() {

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

