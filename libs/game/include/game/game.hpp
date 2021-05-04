#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "progress.hpp"
#include "loaders/level_loader.hpp"

class ISprite;

class Map {
public:
    explicit Map(CreatorLevel *level);

    Map(const Map &map);

    Map();

    bool update();

private:
    std::vector<SpaceBody> _space_objects{};
    std::vector<Star> _stars{};
    SpaceShip _ship{};

    ISprite *_bg{};

    void check_all_collision();
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