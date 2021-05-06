#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "objects.hpp"

namespace pt = boost::property_tree;


class CreatorLevel {
public:
    virtual void create_level() = 0;
    virtual ~CreatorLevel() = 0;
};

class JsonCreateLevel : public CreatorLevel {
public:
    JsonCreateLevel() = delete;

    JsonCreateLevel(std::string path);

    JsonCreateLevel &operator=(const JsonCreateLevel &level) = default;

    void create_level() override;


private:
    std::string _path;
    std::vector <SpaceBody> _objects_active;
    std::vector <Star> _objects_not_active;
    SpaceShip _ship;
    ISprite *_level_texture{};

    void create_ship();

    void create_objects();

    void set_texture();

    IGameObject *load_space_object(pt::ptree &tree, std::string obj_name);
};
