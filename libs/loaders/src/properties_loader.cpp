#include "properties_loader.hpp"
#include "debug/exception.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


JsonPlayerPropertiesLoader::JsonPlayerPropertiesLoader(std::string root_path) {
    if (root_path.empty()) {
        throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
    }
    this->path = root_path;
}

properties_t JsonPlayerPropertiesLoader::load_current_properties(const int player_id) {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    pt::read_json(this->path, tree);


    auto fill_prop = [](pt::ptree &pt) -> properties_t {
        properties_t prop;
        prop.fuel = pt.get<size_t>("fuel");
        prop.health = pt.get<size_t>("health");
        prop.battery = pt.get<size_t>("battery");
        prop.engine_power = pt.get<size_t>("engine_power");
    };

    properties_t prop{};
    for (pt::ptree::value_type &player : tree.get_child("players")) {
        if (player.second.get<size_t>("id") == player_id) {
            prop = fill_prop(player.second.get_child("properties"));
            break;
        }
    }
    if (prop.is_empty()) {
        throw LoadError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
    }

    return prop;
}