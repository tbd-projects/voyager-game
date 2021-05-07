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

void JsonPlayerPropertiesLoader::save_current_properties(const int player_id, properties_t &properties) {
    if (this->path.empty()) {
        throw FileError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
    }
    namespace pt = boost::property_tree;

    auto rewrite = [&player_id](properties_t &properties) -> pt::ptree {
        pt::ptree tree;
        pt::ptree prop;
        tree.put("id", player_id);

        prop.put("fuel", properties.fuel);
        prop.put("health", properties.health);
        prop.put("battery", properties.battery);
        prop.put("engine_power", properties.engine_power);

        tree.put_child("properties", prop);

        return tree;
    };

    pt::ptree tree;
    pt::read_json(this->path, tree);


    pt::ptree temp;
    temp = rewrite(properties);

    bool flag = false;
    for (pt::ptree::value_type &player : tree.get_child("players")) {
        if (player.second.get<size_t>("id") == player_id) {
            player.second = temp;
            flag = true;
        }
    }

    if (!flag) {
        auto &players = tree.get_child("players");
        players.push_back(std::make_pair("", temp));
        tree.put_child("players", players);
    }

    pt::write_json(this->path, tree);
}