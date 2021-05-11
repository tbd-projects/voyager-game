#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <game/objects.hpp>

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

    JsonCreateLevel &operator=(const JsonCreateLevel &level) = delete;

    JsonCreateLevel(const JsonCreateLevel&) = delete;

    void create_level() override;


private:
    std::string _path;
    std::vector <std::shared_ptr<SpaceBody>> _objects_active;
    std::vector <std::shared_ptr<Star>> _objects_not_active;

    Sprite *_level_texture{};
    size_t _bg_id;

    void create_objects();

    void set_texture();

    void load_space_objects(pt::ptree &tree, std::string obj_name);
};
