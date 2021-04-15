#pragma once

#include <vector>
#include "objects.hpp"

class CreatorLevel {
public:
    virtual void create_level() = 0;
    virtual ~CreatorLevel() = 0;
};

class JsonCreateLevel : public CreatorLevel {
public:
    JsonCreateLevel() = delete;

    JsonCreateLevel(std::string &path);

    JsonCreateLevel &operator=(const JsonCreateLevel &level) = default;

    void create_level() override;


private:
    std::string _path;
    std::vector <SpaceBody> _objects_active;
    std::vector <Star> _objects_not_active;
    SpaceShip _ship;
    ISprite *_level_texture;
    std::string _file_path;

    void create_ship();

    void create_objects();

    void set_texture();
};
