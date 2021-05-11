#include "loaders/progress_loader.hpp"
#include "debug/exception.h"
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace game {
    namespace pt = boost::property_tree;

    BaseProgressLoader::BaseProgressLoader(const std::string &root_path) {
        if (root_path.empty()) {
            throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
        }
        this->path = root_path;
    }

    progress_t BaseProgressLoader::load(const int player_id) {

        if (!this->has_progress(player_id)) {
            throw LoadError(__FILE__, typeid(*this).name(), __FUNCTION__, this->path);
        }

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
        return stats;
    }

    void BaseProgressLoader::save(const int player_id, progress_t &progress) {
        auto rewrite = [&]() -> pt::ptree {
            pt::ptree tree;
            tree.put("id", player_id);
            tree.put("stats.time", progress.time);
            tree.put("stats.coins", progress.coins);

            pt::ptree levels;
            for (auto &i : progress.level_stat) {
                pt::ptree temp;
                temp.put("num", i.first);
                temp.put("stars", i.second);
                levels.push_back(std::make_pair("", temp));
            }
            tree.put_child("stats.levels", levels);
            return tree;
        };

        pt::ptree tree;
        pt::read_json(this->path, tree);

        pt::ptree temp;
        temp = rewrite();
//        tree.add_child("stats", temp);

        pt::ptree &players = tree.get_child("players");

        // обновляем пользователя с id = player_id
        if (!this->has_progress(player_id)) {
            players.push_back(std::make_pair("", temp));
        } else {
            for (pt::ptree::value_type &player : players) {
                if (player.second.get<int>("id") == player_id) {
                    player.second= temp;
                }
            }
            tree.put_child("players", players);

            pt::write_json(this->path, tree);

        }
    }

    bool BaseProgressLoader::has_progress(const int player_id) {
        pt::ptree tree;
        pt::read_json(this->path, tree);

        bool has_player = false;

        for (auto &player: tree.get_child("players")) {
            if (player.second.get<int>("id") == player_id) {
                has_player = true;
                break;
            }
        }

        return has_player;

    }
} // namespace game

