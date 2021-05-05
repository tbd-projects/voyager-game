#include "loaders/progress_loader.hpp"
#include "debug/exception.h"
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

BaseProgressLoader::BaseProgressLoader(const std::string &root_path) {
    if (root_path.empty()) {
        throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
    }
    this->path = root_path;
}

progress_t BaseProgressLoader::load(const int player_id) {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    pt::read_json(this->path, tree);

    auto parce_stats = [](pt::ptree &tree) {
        progress_t progress;
        progress.time = tree.get<size_t>("stats.time");
        progress.coins = tree.get<size_t>("stats.coins");
        for (pt::ptree::value_type &level: tree.get_child("stats.levels")) {
            int num = level.second.get<int>("num");
            int stars = level.second.get<int>("stars");
            progress.level_stat.emplace_back(num, stars);
        }
        return progress;
    };
    progress_t stats{};
    for (pt::ptree::value_type &player : tree.get_child("players")) {
        if (player.second.get<int>("id") == player_id) {
            stats = parce_stats(player.second);
            break;
        }
    }
    if (stats.is_empty()) {
        throw LoadError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
    }

    return stats;
}

void BaseProgressLoader::save(const int player_id, progress_t &progress) {
    namespace pt = boost::property_tree;
    auto rewrite = [&progress]() -> pt::ptree {
        pt::ptree tree;
        tree.put("time", progress.time);
        tree.put("coins", progress.coins);

        pt::ptree levels;
        for (auto &i : progress.level_stat) {
            pt::ptree temp;
            temp.put("num", i.first);
            temp.put("stars", i.second);
            levels.push_back(std::make_pair("", temp));
        }
        tree.put_child("levels", levels);
        return tree;
    };

    pt::ptree tree;
    pt::read_json(this->path, tree);

    pt::ptree temp;
    temp = rewrite();
    // обновляем пользователя с id = player_id
    pt::ptree cur;
    cur.put("id", player_id);
    cur.add_child("stats", temp);

    pt::ptree players;
    bool flag = false;
    for (pt::ptree::value_type &player : tree.get_child("players")) {
        if (player.second.get<int>("id") == player_id) {
            players.push_back(std::make_pair("", cur));
            flag = true;
        } else {
            players.push_back(player);
        }
    }
    if (!flag) {
        players.push_back(std::make_pair("", temp));
    }
    tree.put_child("players", players);

    pt::write_json(this->path, tree);

}
