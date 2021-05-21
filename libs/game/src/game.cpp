#include <stdexcept>
#include <game_manager/commands.hpp>
#include <game_manager/config.hpp>
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

        auto &config = game_manager::Config::get_instance();

        _storage = std::make_unique<graphics::TextureStorage>(*config.graphics_factory);

        auto &level_manager = dynamic_cast<LevelManager &>(*::game_manager::Config::get_instance().level_manager);

        properties_t properties = config.properties_loader->load_current_properties(player_id);

        auto sprite = config.sprite_loader->load(properties.sprite_id, *_storage);

        auto width = sprite->get_texture_size().first;
        auto height = sprite->get_texture_size().second;

        std::unique_ptr<math::Polygon> pol = std::make_unique<math::TrianglePolygon>(
                math::coords_t(math::decimal_t(0), math::decimal_t(0)), height, width);

        _ship = std::make_unique<SpaceShip>(properties.sprite_id, std::move(sprite), std::move(pol), properties);
        // @todo Follow_pos - width, height of canvas
        this->_camera = std::make_unique<Camera>(_ship, math::coords_t(500, 500));

        this->_timer = std::make_unique<Timer>();
    }

    void Map::load_level(size_t level_num) {
        auto &config = ::game_manager::Config::get_instance();
        auto &level_manager = dynamic_cast<LevelManager &>(*config.level_manager);

        level_manager.set_current_level(level_num);
        level_manager.load_current_level();

        auto &current_level = dynamic_cast<JsonCreateLevel &>(*level_manager._current_level);
        _space_objects = current_level.get_planets();
        _stars = current_level.get_stars();
        _bg_id = current_level.get_bg_id();

        auto &factory = *config.sprite_loader;

        for (auto &planet : this->_space_objects) {
            planet->set_sprite(factory.load(planet->get_sprite_id(), *_storage));
        }
        for (auto &star : this->_stars) {
            star->set_sprite(factory.load(star->get_sprite_id(), *_storage));
        }

        _bg = factory.load(_bg_id, *_storage);

        auto sizes = _bg->get_texture_size();

        _bg->set_pos(math::coords_t(sizes.first / 2, sizes.second / 2));

        for (auto &obj : _space_objects) {
            _engine.add_object(obj);
        }
        for (auto &obj : _stars) {
            _engine.add_object(obj);
        }

        _engine.add_object(_ship);

        this->_timer->start();
    }

    bool Map::update(graphics::ICanvas &canvas) {
        _bg->set_pos(_camera->get_position(math::coords_t(canvas.get_width() / 2, canvas.get_height() / 2)));
        _bg->draw(canvas);

        for (auto &obj : this->_space_objects) {
            // obj->move(_engine);

            auto &sprite = obj->get_sprite();
            sprite->set_pos(_camera->get_position(obj->get_pos()));
            sprite->draw(canvas);
        }
        for (auto &obj : this->_stars) {
            auto &sprite = obj->get_sprite();
            sprite->set_pos(_camera->get_position(obj->get_pos()));
            sprite->draw(canvas);
        }

        _ship->move(_engine);
        auto &sprite = _ship->get_sprite();
        sprite->set_pos(_camera->get_position(_ship->get_pos()));
        sprite->set_rotation(_ship->get_polygon()->get_rotation());
        sprite->draw(canvas);

        return true;
    }

    void Map::set_impulse(math::decimal_t angle) {
        this->_ship->add_impulse(angle);
    }

    std::shared_ptr<event_controller::ICommand> Map::process_keyboard(event_controller::KeyboardEvent &ev) {

        switch (ev.key) {
            case event_controller::Key::Escape:
                return std::make_shared<game_manager::command::EndGame>();
            case event_controller::Key::W:
                set_impulse(0);
                break;
            case event_controller::Key::S:
                set_impulse(180);
                break;
            case event_controller::Key::D:
                set_impulse(-90);
                break;
            case event_controller::Key::A:
                set_impulse(90);
                break;
            default:
                break;
        }
        return std::make_shared<game_manager::command::DoNothing>();
    }

    bool Map::update_ship(ship_character type) {
        bool is_live = true;
        switch (type) {
            case FUEL:
                is_live *= this->_ship->update_fuel();
                break;
            case BATTERY:
                is_live *= this->_ship->update_battery();
                break;

            default:
                break;
        }
        std::cout<<"BATTERY " << this->_ship->get_battery() <<std::endl;
        std::cout<<"FUEL " << this->_ship->get_fuel() <<std::endl;

        return is_live;
    }

// Game

    Game::Game(event_controller::IController &controller, graphics::ICanvas &canvas) :
            _map(game_manager::Config::get_instance().player_id),
            _canvas(canvas),
            _controller(controller),
            fps_counter(0) {
        _controller.subscribe(event_controller::EventType::fps, *this);
        _controller.subscribe(event_controller::EventType::keyboard, *this);
        _controller.subscribe(event_controller::EventType::close, *this);
    }

    Game::~Game() {
        _controller.unsubscribe(event_controller::EventType::fps, *this);
        _controller.unsubscribe(event_controller::EventType::keyboard, *this);
        _controller.unsubscribe(event_controller::EventType::close, *this);
    }

    bool Game::start_game(int level) {
        _map.load_level(level);
        return true;
    }

    bool Game::stop_game() {
        return false;
    }

    std::shared_ptr<event_controller::ICommand> Game::update(event_controller::Event &event) {

        auto &config = ::game_manager::Config::get_instance();
        if (fps_counter % config.fps == 0) {
            fps_counter = 0;
        }
        ++fps_counter;

        bool is_live = false;

        switch (event.type) {
            case event_controller::EventType::fps:
                _map.update(_canvas);
                if (this->fps_counter % config.fps == 0) {
                    is_live = this->_map.update_ship(BATTERY);
                }
                break;

            case event_controller::EventType::close:
                return std::make_shared<game_manager::command::Exit>();
            case event_controller::EventType::keyboard: {
                auto key = dynamic_cast<event_controller::KeyboardEvent &>(event);
                is_live = this->_map.update_ship(FUEL);
                return this->_map.process_keyboard(key);
            }
            default:
                break;
        }

        return std::make_shared<game_manager::command::DoNothing>();
    }
} // namespace game

