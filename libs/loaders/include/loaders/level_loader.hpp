#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "game/objects.hpp"
#include "game/interface.hpp"

namespace game::external {
namespace pt = boost::property_tree;

class JsonCreateLevel : public CreatorLevel {
  public:
    JsonCreateLevel() = default;

    explicit JsonCreateLevel(const std::string &level_dir);

    size_t get_levels_count() override;

//        JsonCreateLevel &operator=(const JsonCreateLevel &level) = delete;

//        JsonCreateLevel(const JsonCreateLevel &) = delete;

    void create_level(size_t level_num) override;

    std::vector<std::shared_ptr<SpaceBody>> &&get_planets() override;

    std::vector<std::shared_ptr<Star>> &&get_stars() override;

    size_t get_bg_id() const override { return this->_bg_id; };

    math::decimal_t get_fuel_density() const override { return this->_density; }

  private:
    std::string _path;
    std::vector<std::shared_ptr<SpaceBody>> _objects_active;
    std::vector<std::shared_ptr<Star>> _objects_not_active;
    size_t _bg_id;
    math::decimal_t _density;

    void create_objects();

    void set_texture();

    void load_star(pt::ptree::value_type &star);

    void load_planet(pt::ptree::value_type &planet);

    void load_space_objects(pt::ptree &tree, const std::string &obj_name);

};

} // namespace game
