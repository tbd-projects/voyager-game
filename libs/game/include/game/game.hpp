#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "progress.hpp"
#include "loaders/level_loader.hpp"
#include "sprite_creator.hpp"
#include "camera.hpp"
#include <graphics/i_drawable.h>
#include <event_controller/i_controller.h>
#include <event_controller/i_subscriber.h>
#include <event_controller/event/keyboard_event.h>

namespace game {
    class Map {
    public:
        explicit Map(size_t player_id);

        Map() = delete;

        Map(const Map &map) = delete;

        Map &operator=(const Map &) = delete;

        void load_level(size_t level_num);

        void set_impulse(math::decimal_t angle);

        bool update(graphics::ICanvas &canvas);

        std::shared_ptr<event_controller::ICommand> process_keyboard(event_controller::KeyboardEvent &ev);


    private:
        std::unique_ptr<graphics::TextureStorage> _storage;
        std::vector<std::shared_ptr<SpaceBody>> _space_objects;
        std::vector<std::shared_ptr<Star>> _stars;
        std::shared_ptr<SpaceShip> _ship;
        std::unique_ptr<graphics::Sprite> _bg;
        size_t _bg_id = 0;

        physics::Engine _engine;
        std::unique_ptr<Camera> _camera;

        void check_all_collision();

        void set_sprites(MapSpriteCreator &factory);



//    void create_ship(size_t player_id);

//    void create_level();
    };

    class Game : public event_controller::ISubscriber {
    public:
        explicit Game(event_controller::IController &controller, graphics::ICanvas &canvas);

        ~Game();

        std::shared_ptr<event_controller::ICommand> update(event_controller::Event &event) override;

        bool start_game(int level);

        bool stop_game();

    private:
        game::Map _map;
        game::Progress _progress;
        graphics::ICanvas &_canvas;
        event_controller::IController &_controller;

    };

} // namespace game