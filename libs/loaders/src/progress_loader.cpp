// Дмитрий Варин
#include "loaders/progress_loader.hpp"
#include "debug/exception.hpp"
#include <boost/property_tree/json_parser.hpp>


namespace game::external {
    BaseProgressLoader::BaseProgressLoader(const std::string &root_path) {
        if (root_path.empty()) {
            throw debug::INVALID_ARG_ERROR();
        }
        this->path = root_path;
    }

    progress_t BaseProgressLoader::load(size_t player_id) {
        if (!this->has_progress(player_id)) {
            throw debug::ARG_LOAD_ERROR(this->path);
        }

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(this->path, tree);

        auto parce_stats = [](boost::property_tree::ptree &tree) {
            progress_t progress;
            progress.coins = tree.get<size_t>("stats.coins");
            for (boost::property_tree::ptree::value_type &level :
                    tree.get_child("stats.levels")) {
                level_stat cur_level{};
                cur_level.num = level.second.get<unsigned int>("num");
                cur_level.stars = level.second.get<unsigned char>("stars");
                cur_level.time_as_seconds =
                        level.second.get<unsigned int>("time");
                cur_level.is_win = level.second.get<bool>("is_win");
                progress.levels.push_back(cur_level);
            }
            return progress;
        };

        progress_t stats{};
        for (boost::property_tree::ptree::value_type &player : tree.get_child("players")) {
            if (player.second.get<size_t>("id") == player_id) {
                stats = parce_stats(player.second);
                break;
            }
        }
        return stats;
    }

    void BaseProgressLoader::save(size_t player_id, progress_t &progress) {
        auto rewrite = [&]() -> boost::property_tree::ptree {
            boost::property_tree::ptree tree;
            tree.put("id", player_id);
            tree.put("stats.coins", progress.coins);

            boost::property_tree::ptree levels;
            for (auto &i : progress.levels) {
                boost::property_tree::ptree temp;
                temp.put("num", i.num);
                temp.put("stars", i.stars);
                temp.put("time", i.time_as_seconds);
                temp.put("is_win", i.is_win);
                levels.push_back(std::make_pair("", temp));
            }
            tree.put_child("stats.levels", levels);
            return tree;
        };

        boost::property_tree::ptree tree;
        boost::property_tree::read_json(this->path, tree);

        boost::property_tree::ptree temp;
        temp = rewrite();

        boost::property_tree::ptree &players = tree.get_child("players");

        // обновляем пользователя с id = player_id
        if (!this->has_progress(player_id)) {
            players.push_back(std::make_pair("", temp));
        } else {
            for (boost::property_tree::ptree::value_type &player : players) {
                if (player.second.get<size_t>("id") == player_id) {
                    check_update_win(player.second, temp);
                    player.second = temp;
                }
            }
            tree.put_child("players", players);

            boost::property_tree::write_json(this->path, tree);
        }
    }

    bool BaseProgressLoader::has_progress(size_t player_id) {
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(this->path, tree);

        bool has_player = false;

        for (auto &player : tree.get_child("players")) {
            if (player.second.get<size_t>("id") == player_id) {
                has_player = true;
                break;
            }
        }

        return has_player;
    }

void BaseProgressLoader::check_update_win(boost::property_tree::ptree &tree, boost::property_tree::ptree &new_tree) {
    for (auto &level : tree.get_child("stats.levels")) {
        auto num = level.second.get<unsigned int>("num");
        auto status = level.second.get<bool>("is_win");
        for (auto &new_level : new_tree.get_child("stats.levels")) {
            if (new_level.second.get<unsigned int>("num") == num) {
                if (!new_level.second.get<bool>("is_win") && status) {
                    new_level.second.put("is_win", status);
                }
            }
        }
    }
}


}  // namespace game::external

