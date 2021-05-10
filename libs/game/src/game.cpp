#include <stdexcept>
#include "game.hpp"


bool Map::update() {
    return false;
}

void Map::check_all_collision() {

}

void Map::set_sprites(MapSpriteCreator& factory) {
    for (auto& planet : this->_space_objects) {
        planet->set_sprite(factory.get_sprite(planet->get_sprite_id()));
    }

}



// Game

//Game::Game(IController *controller) {
//
//}

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

