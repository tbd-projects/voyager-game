#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "game/objects.hpp"
#include "game/exceptions.hpp"


namespace game {
    namespace pt = boost::property_tree;

    class CreatorLevel {
    public:
        virtual void create_level(size_t level_num) = 0;
        virtual size_t get_levels_count() = 0;
        virtual size_t get_current_level() const;
        virtual ~CreatorLevel() = default;
    };

    class JsonCreateLevel : public CreatorLevel {
    public:
        JsonCreateLevel() = default;

        explicit JsonCreateLevel(const std::string &level_dir);

        size_t get_levels_count() override;
//        JsonCreateLevel &operator=(const JsonCreateLevel &level) = delete;

//        JsonCreateLevel(const JsonCreateLevel &) = delete;

        void create_level(size_t level_num) override;

        void load_star(pt::ptree::value_type &star);

        void load_planet(pt::ptree::value_type &planet);


        std::vector<std::shared_ptr<SpaceBody>> &&get_planets();

        std::vector<std::shared_ptr<Star>> &&get_stars();

        size_t get_bg_id() const { return this->_bg_id; };
        math::decimal_t get_fuel_density() const {return this->_density;}


    private:
        std::string _path;
        std::vector<std::shared_ptr<SpaceBody>> _objects_active;
        std::vector<std::shared_ptr<Star>> _objects_not_active;
        size_t _bg_id;
        math::decimal_t _density;

        void create_objects();

        void set_texture();

        void load_space_objects(pt::ptree &tree, const std::string &obj_name);
    };

    class LevelManager : public CreatorLevel {
    public:
        LevelManager();

        void set_current_level(size_t level_num);

        [[nodiscard]] size_t get_current_level() const override {return this->_level_num;}

        void load_current_level();

        size_t get_levels_count() override;

        void create_level(size_t level_num) override;

        std::unique_ptr<CreatorLevel> _current_level;
    private:
        size_t _level_num;
    };
} // namespace game
