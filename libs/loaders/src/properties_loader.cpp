#include "properties_loader.hpp"
#include "debug/exception.h"


using namespace boost::property_tree;

namespace game {
    JsonPlayerPropertiesLoader::JsonPlayerPropertiesLoader(const std::string &root_path) {
        if (root_path.empty()) {
            throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
        }
        this->path = root_path;
    }

    properties_t JsonPlayerPropertiesLoader::load_current_properties(const int player_id) {

        ptree tree;
        read_json(this->path, tree);


        auto fill_prop = [](ptree &pt) -> properties_t {
            properties_t prop;
            prop.fuel = pt.get<unsigned int>("fuel");
            prop.health = pt.get<unsigned int>("health");
            prop.battery = pt.get<unsigned int>("battery");
            prop.engine_power = pt.get<unsigned int>("engine_power");

            return prop;
        };


        properties_t prop{};
        for (ptree::value_type &player : tree.get_child("players")) {
            if (player.second.get<int>("id") == player_id) {
                prop = fill_prop(player.second.get_child("properties"));
                prop.sprite_id = player.second.get<size_t>("sprite_id");
                break;
            }
        }
//    if (prop.is_empty()) {
//        throw LoadError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
//    }

        return prop;
    }

    void JsonPlayerPropertiesLoader::save_current_properties(const int player_id, properties_t &properties) {
        if (this->path.empty()) {
            throw FileError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
        }
//    namespace pt = boost::property_tree;

        auto rewrite = [&player_id](properties_t &properties) -> ptree {
            ptree tree;
            ptree prop;
            tree.put("id", player_id);
            tree.put("sprite_id", properties.sprite_id);

            prop.put("fuel", properties.fuel);
            prop.put("health", properties.health);
            prop.put("battery", properties.battery);
            prop.put("engine_power", properties.engine_power);

            tree.put_child("properties", prop);

            return tree;
        };

        ptree tree;
        read_json(this->path, tree);


        ptree temp;
        temp = rewrite(properties);

        bool flag = false;
        for (ptree::value_type &player : tree.get_child("players")) {
            if (player.second.get<int>("id") == player_id) {
                player.second = temp;
                flag = true;
            }
        }

        if (!flag) {
            auto &players = tree.get_child("players");
            players.push_back(std::make_pair("", temp));
            tree.put_child("players", players);
        }

        write_json(this->path, tree);
    }
} // namespace game
