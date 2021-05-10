#pragma once

#include <cstddef>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

struct properties_t {
    size_t fuel;
    size_t health;
    size_t battery;
    size_t engine_power;

    bool is_empty() {
        return !fuel && !health && !battery && !engine_power;
    }
};

class PlayerPropertiesLoader {

public:
    virtual properties_t load_current_properties(const int player_id) = 0;

    virtual void save_current_properties(const int player_id, properties_t &properties) = 0;

    virtual ~PlayerPropertiesLoader() = default;

protected:
    std::string path;
};

class JsonPlayerPropertiesLoader : public PlayerPropertiesLoader {
public:
    JsonPlayerPropertiesLoader() = delete;

    JsonPlayerPropertiesLoader(std::string root_path);

    properties_t load_current_properties(const int player_id) override;

    void save_current_properties(const int player_id, properties_t &properties) override;
};

