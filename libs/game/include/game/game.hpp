#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "progress.hpp"
#include "loaders/level_loader.hpp"
#include "sprite_creator.hpp"

class Sprite;

class Map {
public:
    explicit Map(size_t player_id);

    Map() = delete;

    Map(const Map &map) = delete;

    Map &operator=(const Map &) = delete;

    bool update();

private:
    std::vector<std::shared_ptr<SpaceBody>> _space_objects;
    std::vector<std::shared_ptr<Star>> _stars;
    SpaceShip _ship;
    std::unique_ptr<Sprite> _bg;
    size_t _bg_id;

    void check_all_collision();

    void set_sprites(MapSpriteCreator& factory);

    void load_level_data(size_t level_num);

//    void create_ship(size_t player_id);

//    void create_level();
};


class ISubscriber {

};

class IController {

};

class Game : public ISubscriber {
public:
    explicit Game(IController *controller);

    ~Game();

    void update();

    bool start_game();

    bool stop_game();

private:
    Map _map;
    Progress _progress;
};