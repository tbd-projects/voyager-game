// Дмитрий Варин
#include <stdexcept>
#include <game_manager/commands.hpp>
#include <game_manager/config.hpp>
#include "game.hpp"
#include "interface.hpp"
#include <physics/orbit.hpp>

namespace game {

    void Map::set_sprites(MapSpriteCreator &factory) {
        for (auto &planet : this->_space_objects) {
            planet->set_sprite(factory.get_sprite(planet->get_sprite_id()));
        }
        for (auto &star : this->_stars) {
            star->set_sprite(factory.get_sprite(star->get_sprite_id()));
        }
        this->_bg = factory.get_sprite(_bg_id);
    }

    Map::Map(size_t player_id) :
            _storage(
                    std::make_unique<graphics::TextureStorage>(*game_manager::Config::get_instance().graphics_factory)),
            _timer(std::make_unique<Timer>()),
            _game_screen(std::make_unique<menu::GameScreen>(*game_manager::Config::get_instance().graphics_factory,
                                                            *game_manager::Config::get_instance().sprite_loader,
                                                            *_storage)) {

        auto &config = game_manager::Config::get_instance();

        auto properties = config.properties_loader->load_current_properties(player_id);

        auto sprite = config.sprite_loader->load(properties.sprite_id, *_storage);

        std::unique_ptr<math::Polygon> pol = std::make_unique<math::TrianglePolygon>(
                math::coords_t(math::decimal_t(0), math::decimal_t(0)), sprite->get_texture_size().first,
                sprite->get_texture_size().second);

        auto fuel_mass = _engine.get_mass_fuel_by_one_impulse();
        // default params
        const math::Vector2d init_velocity = math::Vector2d(math::coords_t(0, 0));
        const size_t init_weight = 1;
        const math::coords_t init_pos = math::coords_t(0, 0);

        _ship = std::make_unique<SpaceShip>(properties.sprite_id, std::move(sprite), std::move(pol), properties,
                                            fuel_mass, init_weight, init_velocity, init_pos);
        this->_camera = std::make_unique<Camera>(_ship);

        _camera->set_center(math::coords_t(500, 500));

        _game_screen->update(this->_timer->get_s().count(), this->_ship->get_fuel(), this->_ship->get_battery());
    }

    void Map::load_level(size_t level_num) {
        auto &config = ::game_manager::Config::get_instance();

        auto &current_level = (*config.levels_loader);
        current_level.create_level(level_num);

        _space_objects = current_level.get_planets();
        _stars = current_level.get_stars();
        _bg_id = current_level.get_bg_id();
        this->init_ship(current_level.get_ship_character());

        auto &factory = *config.sprite_loader;

        for (auto &planet : this->_space_objects) {
            planet->set_sprite(factory.load(planet->get_sprite_id(), *_storage));
            math::decimal_t size = planet->get_polygon()->get_circumscribed_circ();
            planet->get_sprite()->set_size({size, size});
        }
        for (auto &star : this->_stars) {
            star->set_sprite(factory.load(star->get_sprite_id(), *_storage));
            math::decimal_t size = star->get_polygon()->get_circumscribed_circ();
            star->get_sprite()->set_size({size, size});
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
        const static auto center = math::coords_t(canvas.get_width() / 2, canvas.get_height() / 2);

        _ship->move(_engine);

        _camera->update();
        _camera->apply(*_bg, center);

        _bg->draw(canvas);

        auto shape = game_manager::Config::get_instance().graphics_factory->create_orbit();
        shape->set_color(Color(255,255,255,128));

        for (auto &obj : this->_space_objects) {
            auto orbit = obj->get_orbit().get_orbit_properties();
            shape->set_orbit(orbit);


            shape->set_pos(_camera->get_coords(orbit.basis));
            shape->scale(_camera->get_size());
            shape->draw(canvas);

            math::decimal_t radius = _engine.get_effective_circle_orbit(*obj);
            orbit = physics::Orbit::orbit_properties_t{
                    math::coords_t(radius, radius), obj->get_pos(), {}, {}};
            shape->set_orbit(orbit);

            shape->set_pos(_camera->get_coords(orbit.basis));
            shape->scale(_camera->get_size());
            shape->draw(canvas);
        }


        for (auto &obj : this->_space_objects) {
            obj->move(_engine);

            _camera->apply_object(*obj);

            obj->get_sprite()->draw(canvas);
        }

        for (auto &obj : this->_stars) {
            _camera->apply_object(*obj);
            obj->get_sprite()->draw(canvas);
        }

        if (_ship->is_die() || _engine.check_collision(*_ship)) {
            return false;
        }
        _camera->apply_object(*_ship);
        auto &sprite = _ship->get_sprite();
        sprite->set_rotation(_ship->get_polygon()->get_rotation());


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
                break;
            case event_controller::Key::D:
                this->_ship->add_rotation(-angle);
                break;
            case event_controller::Key::W:
                this->set_impulse(this->_ship);
                break;
            case event_controller::Key::S:
                this->_ship->add_impulse(this->_ship->get_rotation() - 180);
                break;
            default:
                break;
        }
        return std::make_shared<game_manager::command::DoNothing>();
    }

    bool Map::update_ship(ship_character type) {

        _game_screen->update(_timer->get_s().count(), _ship->get_fuel(), _ship->get_battery());

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

        return is_live;
    }

    void Map::set_impulse(std::shared_ptr<GameObject> obj) {
        this->set_rotate(obj->get_rotation());
    }

    Timer &Map::get_timer() {
        return *_timer;
    }

    void Map::init_ship(ship_init_t &&inits) {
        this->_ship->set_fuel_density(inits.density);
        this->_ship->set_pos(inits.pos);
        this->_ship->set_velocity(inits.velocity);
        this->_ship->set_weight(inits.weight);
    }

// Game

    Game::Game(event_controller::IController &controller, graphics::ICanvas &canvas) :
            _map(game_manager::Config::get_instance().player_id),
            _canvas(canvas),
            _controller(controller),
            _progress(game_manager::Config::get_instance().progress_loader->load(
                    game_manager::Config::get_instance().player_id)),
            fps_counter(0),
            _id_level(0) {
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
        _id_level = level;
        return true;
    }

    void Game::stop_game() {
        _map.get_timer().pause();
        _unsibscribe_events();
    }

    void Game::update_stats(bool is_live) {
        level_stat result{};
        result.time_as_seconds = _map.get_timer().get_s().count();
        result.num = _id_level;
        result.is_win = is_live;
        result.stars = 0;
        this->_progress.update_level(result.num, result);
        game_manager::Config::get_instance().progress_loader->save(game_manager::Config::get_instance().player_id,
                                                                   this->_progress.get_progress());
    }

    std::shared_ptr<event_controller::ICommand> Game::update(event_controller::Event &event) {

        auto &config = ::game_manager::Config::get_instance();
        if (fps_counter % config.fps == 0) {
            fps_counter = 0;
        }
        ++fps_counter;

        bool is_live = _map.update(_canvas);;


        switch (event.type) {
            case event_controller::EventType::fps:
                is_live = _map.update(_canvas);
                if (is_live) {
                    if (this->fps_counter % config.fps == 0) {
                        is_live = this->_map.update_ship(BATTERY);
                    }
                }
                if (!is_live) {
                    _map.get_timer().stop();
                    this->update_stats(is_live);
                    this->stop_game();
                    return std::make_shared<game_manager::command::EndGame>(is_live,
                                                                            this->_progress.get_level_stat(_id_level));
                }
                break;

            case event_controller::EventType::close:
                return std::make_shared<game_manager::command::Exit>();
            case event_controller::EventType::keyboard: {
                auto key = dynamic_cast<event_controller::KeyboardEvent &>(event);
                is_live = this->_map.update_ship(FUEL);
                if (!is_live) {
                    _map.get_timer().stop();
                    this->update_stats(is_live);
                    this->stop_game();
                    return std::make_shared<game_manager::command::EndGame>(is_live,
                                                                            this->_progress.get_level_stat(_id_level));
                }
                if (key.key == event_controller::Key::L) {
                    return std::make_shared<game_manager::command::EndGame>(true
                                                                            , _progress.get_level_stat(_id_level));
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

