#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "exception.hpp"
//#include "game/exceptions.hpp"
#include "loaders/level_loader.hpp"
#include "math.hpp"
#include <memory>
#include "objects.hpp"
#include "physics/orbit.hpp"

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

    void JsonCreateLevel::load_space_objects(pt::ptree &tree, const std::string &obj_name) {
        for (pt::ptree::value_type &planet : tree.get_child(obj_name)) {

            physics::Orbit::orbit_properties_t orb_prop;

            math::coords_t orbit_pos;
            orbit_pos.x = planet.second.get<float>("orbit_properties.x_c");
            orbit_pos.y = planet.second.get<float>("orbit_properties.y_c");
            orb_prop.pos = orbit_pos;

            math::coords_t orbit_var;
            orbit_var.x = planet.second.get<size_t>("a");
            orbit_var.y = planet.second.get<size_t>("b");
            orb_prop.variables = orbit_var;

            math::coords_t velocity;
            velocity.x = planet.second.get<size_t>("velocity.x");
            velocity.y = planet.second.get<size_t>("velocity.y");

            auto weight = planet.second.get<size_t>("weight");

            math::coords_t position;
            position.x = planet.second.get<size_t>("pos.x");
            position.y = planet.second.get<size_t>("pos.y");

            auto height = planet.second.get<size_t>("polygon.height");
            auto width = planet.second.get<size_t>("polygon.width");
            auto angle = planet.second.get<size_t>("polygon.angle");
            auto polygon_type = planet.second.get<std::string>("polygon.type");

            std::unique_ptr<math::Polygon> polygon;
            if (polygon_type == "rectangle") {
                polygon = std::make_unique<math::RectanglePolygon>(position, height, width, angle);
            } else {
                throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
            }


            auto sprite_id = planet.second.get<size_t>("sprite_id");
            if (obj_name == "planets") {
                std::shared_ptr<SpaceBody> obj = std::make_shared<SpaceBody>(sprite_id, nullptr, std::move(polygon),
                                                                             weight,
                                                                             math::Vector2d(velocity), position,
                                                                             orb_prop);
                this->_objects_active.push_back(obj);

            } else if (obj_name == "stars") {
                std::shared_ptr<Star> obj = std::make_shared<Star>(sprite_id, nullptr, std::move(polygon), position,
                                                                   math::Vector2d(velocity), weight);
                this->_objects_not_active.push_back(obj);
            } else {
                throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
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

    void LevelManager::set_current_level(size_t level_num) {
        this->_level_num = level_num;
    }

    void LevelManager::load_current_level() {
        if (!this->_level_num) {
            throw LogicError(__FILE__, typeid(*this).name(), __FUNCTION__, "level num is incorrect");
        }
        this->_current_level->create_level(this->_level_num);
    }
} // namespace game
