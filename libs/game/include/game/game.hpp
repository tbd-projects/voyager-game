#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "progress.hpp"
#include "loaders/level_loader.hpp"
#include "sprite_creator.hpp"

namespace event_controller {
    class IController {

    };
    class ICommand {

    };
}
namespace graphics {
    class ICanvas {

    };
}
namespace game {
    class Sprite;


    class Map {
    public:
        explicit Map(size_t player_id);

        Map() = delete;

        Map(const Map &map) = delete;

        Map &operator=(const Map &) = delete;

        void load_level(size_t level_num);

        bool update(ICanvas &canvas);

    private:
        std::vector<std::shared_ptr<SpaceBody>> _space_objects;
        std::vector<std::shared_ptr<Star>> _stars;
        std::unique_ptr<SpaceShip> _ship;
        std::unique_ptr<Sprite> _bg;
        size_t _bg_id;

        void check_all_collision();

        void set_sprites(MapSpriteCreator &factory);


//    void create_ship(size_t player_id);

//    void create_level();
    };


    class ISubscriber {

    };



    class Game : public ISubscriber {
    public:
        explicit Game(event_controller::IController &controller, graphics::ICanvas &canvas);

        ~Game();

        std::shared_ptr<event_controller::ICommand > update();

        bool start_game(int level);

        bool stop_game();

    private:
        game::Map _map;
        game::Progress _progress;
        graphics::ICanvas _canvas;

    };

} // namespace game