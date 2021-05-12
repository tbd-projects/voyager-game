#include <stdexcept>
//#include <game_manager/commands/nothing_command.hpp>
#include "game.hpp"

namespace game {

    void Map::check_all_collision() {

    }

    void Map::set_sprites(MapSpriteCreator &factory) {
        for (auto &planet : this->_space_objects) {
            planet->set_sprite(factory.get_sprite(planet->get_sprite_id()));
        }
        for (auto &star : this->_stars) {
            star->set_sprite(factory.get_sprite(star->get_sprite_id()));
        }
        this->_bg = factory.get_sprite(_bg_id);
    }
// not usage
//void Map::create_ship(size_t player_id) {
//    properties_t properties = config.properties_loader.load_current_properties(player_id);
//    auto sprite = ISprite(properties.sprite_id);
//    std::unique_ptr<math::Polygon> pol = std::make_unique<math::TrianglePolygon>(
//            math::coords_t(math::decimal_t(0), math::decimal_t(0)), sprite.get_height(), sprite.get_width());
//    this->_ship(properties.sprite_id, nullptr, std::move(pol), properties);
//}

    Map::Map(size_t player_id) {
        // Init spaceShip
//    properties_t properties = config.properties_loader.load_current_properties(player_id);
//    auto sprite = ISprite(properties.sprite_id);
//    std::unique_ptr<math::Polygon> pol = std::make_unique<math::TrianglePolygon>(
//            math::coords_t(math::decimal_t(0), math::decimal_t(0)), sprite.get_height(), sprite.get_width());
//    this->_ship(properties.sprite_id, nullptr, std::move(pol), sprite.get_height(), sprite.get_width());
    }

    void Map::load_level(size_t level_num) {
//    ::game_manager::Config::get_instance().level_manager.set_current_level(level_num);
//    ::game_manager::Config::get_instance().level_manager.load_current_level(level_num);
//    this->_space_objects = ::game_manager::Config::get_instance().level_manager->_current_level.get_planets();
//    this->_stars = ::game_manager::Config::get_instance().level_manager->_current_level.get_stars();
//    this->_bg_id = ::game_manager::Config::get_instance().level_manager->_current_level.get_bg_id();
    }

    bool Map::update(graphics::ICanvas &canvas) {
        for (auto &obj : this->_space_objects) {
            obj->get_sprite()->draw(canvas);
        }
        for (auto &obj : this->_stars) {
            obj->get_sprite()->draw(canvas);
        }
        this->_ship->get_sprite()->draw(canvas);
        
        return true;
    }



// Game

Game::Game(event_controller::IController &controller, graphics::ICanvas &canvas) : _map(0), _canvas(canvas) {

}

    Game::~Game() {

    }

    bool Game::start_game(int level) {
        return false;
    }

    bool Game::stop_game() {
        return false;
    }

    std::shared_ptr<event_controller::ICommand> Game::update(event_controller::Event &event) {
//        return std::make_shared<game_manager::command::NothingCommand>();
            return nullptr;
    }
} // namespace game

