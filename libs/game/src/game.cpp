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

        std::unique_ptr <math::Polygon> pol = std::make_unique<math::TrianglePolygon>(
                math::coords_t(math::decimal_t(0), math::decimal_t(0)), height, width);
        auto fuel_mass = _engine.get_mass_fuel_by_one_impulse();
        _ship = std::make_unique<SpaceShip>(properties.sprite_id, std::move(sprite), std::move(pol), properties,
                                            fuel_mass);
        // @todo Follow_pos - width, height of canvas
        this->_camera = std::make_unique<Camera>(_ship, math::coords_t(500, 500));

        this->_timer = std::make_unique<Timer>();

        _game_screen = std::make_unique<menu::GameScreen>(*config.graphics_factory, *config.sprite_loader, *_storage);
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
        auto fuel_density = current_level.get_fuel_density();

        this->_ship->set_fuel_density(fuel_density);

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
             obj->move(_engine);

            auto &sprite = obj->get_sprite();
            sprite->set_pos(_camera->get_position(obj->get_pos()));


//            auto &shape = obj->get_shape();
//            shape.set_pos(_camera->get_position(obj->get_orbit().get_orbit_properties().basis));
//            shape.draw(canvas);

            sprite->draw(canvas);
        }
        for (auto &obj : this->_stars) {
            auto &sprite = obj->get_sprite();
            sprite->set_pos(_camera->get_position(obj->get_pos()));
            sprite->draw(canvas);
        }

        if (_ship->is_die() || _engine.check_collision(*_ship)) {
            return false;
        }
        _ship->move(_engine);
        auto &sprite = _ship->get_sprite();
        sprite->set_pos(_camera->get_position(_ship->get_pos()));
        sprite->set_rotation(_ship->get_polygon()->get_rotation());

//        auto &shape = _ship->get_shape();
//        shape.set_pos(_camera->get_position(_ship->get_orbit().get_orbit_properties().basis));
//        shape.draw(canvas);

        sprite->draw(canvas);

        _game_screen->draw(&canvas);

        return true;
    }

    void Map::set_rotate(math::decimal_t angle) {
        this->_ship->add_impulse(angle);
    }

    std::shared_ptr<event_controller::ICommand> Map::process_keyboard(event_controller::KeyboardEvent &ev) {
        float angle = 2;
        switch (ev.key) {
            case event_controller::Key::Escape:
                return std::make_shared<game_manager::command::RunPause>();
            case event_controller::Key::A:
                this->_ship->add_rotation(angle);
//                set_rotate(0);
                break;
            case event_controller::Key::D:
                this->_ship->add_rotation(-angle);
//                set_rotate(180);
                break;
            case event_controller::Key::W:
                this->set_impulse(this->_ship);
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

        _game_screen->update(_timer->get_s().count(), _ship->get_battery(), _ship->get_fuel());

        return is_live;
    }

    void Map::set_impulse(std::shared_ptr<GameObject> obj) {
        this->set_rotate(obj->get_rotation());
    }

    Timer &Map::get_timer() {
        return *_timer;
    }

// Game

    Game::Game(event_controller::IController &controller, graphics::ICanvas &canvas) :
            _map(game_manager::Config::get_instance().player_id),
            _canvas(canvas),
            _controller(controller),
            fps_counter(0) {
        _subscribe_events();
    }

    void Game::_subscribe_events() {
        _controller.subscribe(event_controller::fps, *this);
        _controller.subscribe(event_controller::keyboard, *this);
        _controller.subscribe(event_controller::close, *this);
    }

    void Game::_unsibscribe_events() {
        _controller.unsubscribe(event_controller::EventType::fps, *this);
        _controller.unsubscribe(event_controller::EventType::keyboard, *this);
        _controller.unsubscribe(event_controller::EventType::close, *this);
    }

    Game::~Game() {
        _unsibscribe_events();
    }

    bool Game::start_game(int level) {
        _map.load_level(level);
        return true;
    }

    bool Game::stop_game() {
        _map.get_timer().pause();
        _unsibscribe_events();
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
                is_live = _map.update(_canvas);
                if (is_live) {
                    if (this->fps_counter % config.fps == 0) {
                        is_live = this->_map.update_ship(BATTERY);
                    }
                }
                if (!is_live) {
                    this->stop_game();
                    return std::make_shared<game_manager::command::EndGame>();
                }
                break;

            case event_controller::EventType::close:
                return std::make_shared<game_manager::command::Exit>();
            case event_controller::EventType::keyboard: {
                auto key = dynamic_cast<event_controller::KeyboardEvent &>(event);
                is_live = this->_map.update_ship(FUEL);
                if (!is_live) {
                    return std::make_shared<game_manager::command::EndGame>();
                }
                return this->_map.process_keyboard(key);
            }
            default:
                break;
        }

        return std::make_shared<game_manager::command::DoNothing>();
    }

    bool Game::unpause() {
        _map.get_timer().unpause();
        _subscribe_events();
        return true;
    }
} // namespace game

