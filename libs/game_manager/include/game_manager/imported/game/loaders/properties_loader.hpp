#pragma once

#include <cstddef>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace game {

struct properties_t {
    unsigned int fuel;
    unsigned int health;
    unsigned int battery;
    unsigned int engine_power;
    unsigned int sprite_id;

    bool is_empty() {
        return !fuel && !health && !battery && !engine_power && !sprite_id;
    }
};

class PlayerPropertiesLoader {
  public:
    virtual properties_t load_current_properties(const int player_id) = 0;

    virtual void
    save_current_properties(const int player_id, properties_t &properties) = 0;

    virtual ~PlayerPropertiesLoader() = default;
};


class JsonPlayerPropertiesLoader : public PlayerPropertiesLoader {
  public:
    JsonPlayerPropertiesLoader() = delete;

    explicit JsonPlayerPropertiesLoader(std::string root_path) {}

    properties_t load_current_properties(const int player_id) override {
        return {0, 0, 0, 0, 0};
    }

    void save_current_properties(const int player_id
                                 , properties_t &properties) override {}
};

}  // namespace game
