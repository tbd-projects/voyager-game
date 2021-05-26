#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "progress.hpp"
#include "sprite_creator.hpp"
#include "camera.hpp"
#include <graphics/i_drawable.h>
#include <event_controller/i_controller.h>
#include <event_controller/i_subscriber.h>
#include <event_controller/event/keyboard_event.h>
#include <menu/game_screen.h>
#include "timer.hpp"

namespace game {
    class Map {
    public:
        explicit Map(size_t player_id);

        Map() = delete;

        Map(const Map &map) = delete;

        Map &operator=(const Map &) = delete;

        void load_level(size_t level_num);

        void set_rotate(math::decimal_t angle);

        void set_impulse(std::shared_ptr<GameObject> obj);

        bool update(graphics::ICanvas &canvas);

        bool update_ship(ship_character type);


        std::shared_ptr<event_controller::ICommand> process_keyboard(event_controller::KeyboardEvent &ev);

        Timer &get_timer();

    private:
        std::unique_ptr<graphics::TextureStorage> _storage;
        std::vector<std::shared_ptr<SpaceBody>> _space_objects;
        std::vector<std::shared_ptr<Star>> _stars;
        std::shared_ptr<SpaceShip> _ship;
        std::unique_ptr<graphics::Sprite> _bg;
        std::unique_ptr<Timer> _timer;
        size_t _bg_id = 0;

        std::unique_ptr<menu::GameScreen> _game_screen;

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

        void update_stats(bool is_live);

        bool start_game(int level);

        void stop_game();
        bool unpause();

    private:
        game::Map _map;
        graphics::ICanvas &_canvas;
        event_controller::IController &_controller;
        game::Progress _progress;
//        progress_t _progress;
        size_t fps_counter;

        size_t _id_level;

        void _subscribe_events();

        void _unsibscribe_events();
    };

} // namespace game