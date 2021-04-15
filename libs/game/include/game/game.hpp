#pragma once

#include <cstddef>
#include <vector>

#include "objects.hpp"
#include "loaders/level_loader.hpp"
#include "loaders/progress_loader.hpp"

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

struct progress_t {
    size_t coins;
    size_t level;
    size_t stars;
    size_t time;
};

class Progress {
public:
    Progress() = default;

    explicit Progress(ProgressLoader *loader);

    explicit Progress(const progress_t &progress);

    Progress &operator=(const Progress &progress);

    ~Progress() = default;

    progress_t &get_progress();

    progress_t &set_progress(progress_t &progress);

private:
    progress_t _progress;

};

class ISubscriber {

};

class IController {

};

class Progress;

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