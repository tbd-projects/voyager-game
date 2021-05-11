#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "objects.hpp"
#include "game/exceptions.hpp"

namespace pt = boost::property_tree;

namespace game {

    class CreatorLevel {
    public:
        virtual void create_level(size_t level_num) = 0;

        virtual ~CreatorLevel() = default;
    };

    class JsonCreateLevel : public CreatorLevel {
    public:
        JsonCreateLevel() = delete;

        JsonCreateLevel(std::string level_dir);

        JsonCreateLevel &operator=(const JsonCreateLevel &level) = delete;

        JsonCreateLevel(const JsonCreateLevel &) = delete;

        void create_level(size_t level_num) override;

        std::vector<std::shared_ptr<SpaceBody>> &&get_planets();

        std::vector<std::shared_ptr<Star>> &&get_stars();

        size_t get_bg_id() { return this->_bg_id; };


    private:
        std::string _path;
        std::vector<std::shared_ptr<SpaceBody>> _objects_active;
        std::vector<std::shared_ptr<Star>> _objects_not_active;
        size_t _bg_id;

        void create_objects();

        void set_texture();

        void load_space_objects(pt::ptree &tree, std::string obj_name);
    };

    class LevelManager : public CreatorLevel {
    public:
        LevelManager() : _level_num(0), _current_level(nullptr) {};

        void set_current_level(size_t level_num);

        void load_current_level();

    private:
        size_t _level_num;
        std::unique_ptr<CreatorLevel> _current_level;
    };
} // namespace game
