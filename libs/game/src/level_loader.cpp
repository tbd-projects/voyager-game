#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "debug/exception.hpp"
#include "game/exceptions.hpp"
#include "loaders/level_loader.hpp"
#include "math.hpp"
#include <memory>
#include "objects.hpp"
#include "physics/orbit.hpp"
#include "game_manager/config.hpp"

#define LogicError BaseExceptions

namespace game {
    JsonCreateLevel::JsonCreateLevel(const std::string &level_dir) {
        if (level_dir.empty()) {
            throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
        }
        this->_path = level_dir;
    }

/* path: data/levels/ levels: 1.json 2.json 3.json.......*/
    void JsonCreateLevel::create_level(size_t level_num) {
        if (!level_num) {
            throw LogicError(__FILE__, typeid(*this).name(), __FUNCTION__, "level num is incorrect");
        }
        pt::ptree tree;
        std::string level_path = this->_path + std::to_string(level_num) + ".json";
        pt::read_json(level_path, tree);

        this->_bg_id = tree.get<size_t>("background.sprite_id");
//    this->_level_texture = new ISprite(background_id);

        this->load_space_objects(tree, "stars");
        this->load_space_objects(tree, "planets");


    }

    void JsonCreateLevel::load_star(pt::ptree::value_type &star) {
        math::coords_t velocity;
        math::coords_t pos;

        velocity.x = star.second.get<math::decimal_t>("velocity.x");
        velocity.y = star.second.get<math::decimal_t>("velocity.y");
        pos.x = star.second.get<int>("pos.x");
        pos.y = star.second.get<int>("pos.y");

        auto weight = star.second.get<size_t>("weight");

        auto angle = star.second.get<math::decimal_t>("polygon.angle");
        auto radius = star.second.get<math::decimal_t>("polygon.radius");
        auto polygon_type = star.second.get<std::string>("polygon.type");

        std::unique_ptr<math::Polygon> polygon;
        if (polygon_type == "circle") {
            polygon = std::make_unique<math::CirclePolygon>(math::coords_t(0, 0), radius, angle);
        } else {
            throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
        }

        auto sprite_id = star.second.get<size_t>("sprite_id");

        std::shared_ptr<Star> obj = std::make_shared<Star>(sprite_id, nullptr, std::move(polygon), pos,
                                                           math::Vector2d(velocity), weight);
        this->_objects_not_active.push_back(obj);
    }

    void JsonCreateLevel::load_planet(pt::ptree::value_type &planet) {
        math::coords_t orbit_pos;
        math::coords_t orbit_var;
        math::decimal_t orbit_angle;
        math::decimal_t orbit_period;

        orbit_pos.x = planet.second.get<math::decimal_t>("orbit_properties.x_c");
        orbit_pos.y = planet.second.get<math::decimal_t>("orbit_properties.y_c");

        orbit_var.x = planet.second.get<math::decimal_t>("orbit_properties.a");
        orbit_var.y = planet.second.get<math::decimal_t>("orbit_properties.b");

        orbit_angle = planet.second.get<math::decimal_t>("orbit_properties.angle");
        orbit_period = planet.second.get<math::decimal_t>("orbit_properties.period");

        physics::Orbit::orbit_properties_t orb_prop(orbit_pos, orbit_var, orbit_angle, orbit_period);

        auto weight = planet.second.get<size_t>("weight");

        auto angle = planet.second.get<math::decimal_t>("polygon.angle");
        auto radius = planet.second.get<math::decimal_t>("polygon.radius");
        auto polygon_type = planet.second.get<std::string>("polygon.type");

        std::unique_ptr<math::Polygon> polygon;
        if (polygon_type == "circle") {
            polygon = std::make_unique<math::CirclePolygon>(math::coords_t(0, 0), radius, angle);
        } else {
            throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
        }

        auto sprite_id = planet.second.get<size_t>("sprite_id");
        std::shared_ptr<SpaceBody> obj = std::make_shared<SpaceBody>(sprite_id, nullptr, std::move(polygon),
                                                                     weight,
                                                                     orb_prop);
        this->_objects_active.push_back(obj);

    }

    void JsonCreateLevel::load_space_objects(pt::ptree &tree, const std::string &obj_name) {
        if (obj_name == "stars") {
            for (pt::ptree::value_type &star : tree.get_child(obj_name)) {
                this->load_star(star);
            }
        } else if (obj_name == "planets") {
            for (pt::ptree::value_type &planet : tree.get_child(obj_name)) {
                this->load_planet(planet);
            }
        }
    }

    void JsonCreateLevel::create_objects() {

    }

    std::vector<std::shared_ptr<SpaceBody>> &&JsonCreateLevel::get_planets() {
        return std::move(this->_objects_active);
    }

    std::vector<std::shared_ptr<Star>> &&JsonCreateLevel::get_stars() {
        return std::move(this->_objects_not_active);
    }

    size_t JsonCreateLevel::get_levels_count() {
        auto path = std::filesystem::path(this->_path);
        using std::filesystem::directory_iterator;
        using fp = bool (*)(const std::filesystem::path &);
        return std::count_if(
                directory_iterator(path),
                directory_iterator{},
                (fp) std::filesystem::is_regular_file
        );
    }

    void LevelManager::set_current_level(size_t level_num) {
        this->_level_num = level_num;
    }

    void LevelManager::load_current_level() {
        if (!this->_level_num) {
            throw LogicError(__FILE__, typeid(*this).name(), __FUNCTION__, "level num is incorrect");
        }
        this->_current_level->create_level(this->_level_num);
    }

    void LevelManager::create_level(size_t level_num) {

    }

    LevelManager::LevelManager() : _current_level(nullptr), _level_num(0) {
        auto root = game_manager::Config::get_instance().levels_path;
        _current_level = std::make_unique<JsonCreateLevel>(root);
    }

    size_t LevelManager::get_levels_count() {
        return 0;
    }
} // namespace game
