// Дмитрий Варин
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "debug/exception.hpp"
#include "loaders/level_loader.hpp"
#include "math.hpp"
#include <memory>
#include "game/objects.hpp"
#include "physics/orbit.hpp"
#include "game_manager/config.hpp"

namespace game::external {

    JsonCreateLevel::JsonCreateLevel(const std::string &level_dir) {
        if (level_dir.empty()) {
            throw debug::INVALID_ARG_ERROR();
        }
        this->_path = level_dir;
    }

/* path: data/levels/ levels: 1.json 2.json 3.json.......*/
    void JsonCreateLevel::create_level(size_t level_num) {
    if (!level_num) {
        throw debug::LogicError(
                __FILE__,
                typeid(*this).name(),
                __FUNCTION__,
                "level num is incorrect");
    }
    pt::ptree tree;
    std::string level_path = \
                this->_path + std::to_string(level_num) + ".json";
    pt::read_json(level_path, tree);

    this->_bg_id = tree.get<size_t>("background.sprite_id");

    this->load_ship_init(tree.get_child("ship"));
    this->load_space_objects(tree, "stars");
    this->load_space_objects(tree, "planets");

    math::coords_t left;
    math::coords_t right;

    left.x = tree.get<math::decimal_t>("border.left.x");
    left.y = tree.get<math::decimal_t>("border.left.y");

    right.x = tree.get<math::decimal_t>("border.right.x");
    right.y = tree.get<math::decimal_t>("border.right.y");

    size_t sprite_id = 8;
    math::decimal_t size = 800;
    size_t weight = 10000;

    for (math::decimal_t cur_x = left.x; cur_x < right.x; cur_x += size * 2) {
        std::unique_ptr<math::Polygon> polygon =
                std::make_unique<math::RectanglePolygon>(
                        math::coords_t(cur_x, left.y),
                        size, size*2);
        std::shared_ptr<Star> obj = \
        std::make_shared<Star>(
                sprite_id, nullptr,
                std::move(polygon), math::coords_t(cur_x, left.y),
                math::Vector2d(math::coords_t(0, 0)), weight);
        this->_objects_not_active.push_back(obj);

        polygon = std::make_unique<math::RectanglePolygon>(
                math::coords_t(cur_x, right.y),
                size, size * 2);
        obj = std::make_shared<Star>(
                sprite_id, nullptr,
                std::move(polygon), math::coords_t(cur_x, right.y),
                math::Vector2d(math::coords_t(0, 0)), weight);
        this->_objects_not_active.push_back(obj);

    }
    for (math::decimal_t cur_y = left.y; cur_y < right.y; cur_y += size * 2) {
        std::unique_ptr<math::Polygon> polygon = \
                std::make_unique<math::RectanglePolygon>(
                        math::coords_t(left.x, cur_y),
                        size * 2, size);
        std::shared_ptr<Star> obj = \
        std::make_shared<Star>(
                sprite_id, nullptr,
                std::move(polygon), math::coords_t(left.x, cur_y),
                math::Vector2d(math::coords_t(0, 0)), weight);
        this->_objects_not_active.push_back(obj);

        polygon = std::make_unique<math::RectanglePolygon>(
                math::coords_t(right.x, cur_y),
                size * 2, size);
        obj = std::make_shared<Star>(
                sprite_id, nullptr,
                std::move(polygon), math::coords_t(right.x, cur_y),
                math::Vector2d(math::coords_t(0, 0)), weight);
        this->_objects_not_active.push_back(obj);

    }
}

    void JsonCreateLevel::load_ship_init(pt::ptree &ship_init) {
        this->_ship_init.density = \
                ship_init.get<math::decimal_t>("density");
        this->_ship_init.pos.x = \
                ship_init.get<math::decimal_t>("init_pos.x");
        this->_ship_init.pos.y = \
                ship_init.get<math::decimal_t>("init_pos.y");

        this->_ship_init.velocity = \
                math::Vector2d(
                math::coords_t(
                        ship_init.get<math::decimal_t>("init_velocity.x"),
                        ship_init.get<math::decimal_t>("init_velocity.y")));
        this->_ship_init.weight = \
                ship_init.get<size_t>("init_weight");
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
            polygon = \
                    std::make_unique<math::CirclePolygon>(
                    math::coords_t(0, 0),
                    radius,
                    angle);
        } else {
            throw debug::INVALID_ARG_ERROR();
        }

        auto sprite_id = star.second.get<size_t>("sprite_id");

        std::shared_ptr<Star> obj = \
                std::make_shared<Star>(sprite_id,
                                       nullptr,
                                       std::move(polygon),
                                       pos,
                                       math::Vector2d(velocity),
                                       weight);
        this->_objects_not_active.push_back(obj);
    }

    void JsonCreateLevel::load_planet(pt::ptree::value_type &planet) {
        math::coords_t orbit_pos;
        math::coords_t orbit_var;
        math::decimal_t orbit_angle;
        math::decimal_t orbit_period;

        orbit_pos.x = \
                planet.second.get<math::decimal_t>("orbit_properties.x_c");
        orbit_pos.y = \
                planet.second.get<math::decimal_t>("orbit_properties.y_c");

        orbit_var.x = \
                planet.second.get<math::decimal_t>("orbit_properties.a");
        orbit_var.y = \
                planet.second.get<math::decimal_t>("orbit_properties.b");

        orbit_angle = \
                planet.second.get<math::decimal_t>("orbit_properties.angle");
        orbit_period = \
                planet.second.get<math::decimal_t>("orbit_properties.period");

        physics::Orbit::orbit_properties_t orb_prop(orbit_var,
                                                    orbit_pos,
                                                    orbit_angle,
                                                    orbit_period);

        auto weight = planet.second.get<size_t>("weight");

        auto angle = planet.second.get<math::decimal_t>("polygon.angle");
        auto radius = planet.second.get<math::decimal_t>("polygon.radius");
        auto polygon_type = planet.second.get<std::string>("polygon.type");

        std::unique_ptr<math::Polygon> polygon;
        if (polygon_type == "circle") {
            polygon =
                    std::make_unique<math::CirclePolygon>(
                            math::coords_t(0, 0),
                            radius,
                            angle);
        } else {
            throw debug::INVALID_ARG_ERROR();
        }

        auto sprite_id = planet.second.get<size_t>("sprite_id");
        std::shared_ptr<SpaceBody> obj = \
                std::make_shared<SpaceBody>(sprite_id,
                                            nullptr,
                                            std::move(polygon),
                                            weight,
                                            orb_prop);
        this->_objects_active.push_back(obj);
    }

    void JsonCreateLevel::load_space_objects(
            pt::ptree &tree,
            const std::string &obj_name) {
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
                (fp) std::filesystem::is_regular_file);
    }

    ship_init_t JsonCreateLevel::get_ship_character() const {
        return this->_ship_init;
    }

}  // namespace game::external
