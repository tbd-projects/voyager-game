#pragma once

#include "objects.hpp"
#include "level_loader.hpp"
#include "loaders/progress_loader.hpp"

class Texture;

class Map : {
public:
    Map(CreatorLevel *level);

    Map(const Map &map);

    Map() = delete;

    bool update();

private:
    std::vector <SpaceBody> _space_objects;
    std::vector <Star> _stars;
    SpaceShip _ship;

    Texture _bg;

    void check_all_collision();
};

struct progress_t {
    size_t coins;
    size_t level;
    size_t stars;
    size_t time;
};
class Progress : {
public:
    Progress() = delete;

    Progress(ProgressLoader *loader);

    Progress(const progress_t &progress);

    Progress& operator=(const Progress& progress);

    ~Progress() = default;

    progress_t &get_progress();

    progress_t &set_progress(progress_t &progress);

private:
    progress_t _progress;

};

class ISubscriber;

class Progress;

class Game : public ISubscriber {
public:
    Game(IController *controller);

    ~Game();

    void update();

    bool start_game();

    bool stop_game();

private:
    Map _map;
    Progress _progress;
};