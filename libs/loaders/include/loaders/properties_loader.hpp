#pragma once

struct Properties {
    size_t fuel;
    size_t health;
    size_t battery;
    size_t engine_power;
};

class PlayerPropertiesLoader {
public:
    virtual Properties &load_current_properties() = 0;

    virtual void save_current_properties(Properties &properties) = 0;

};

class JsonPlayerPropertiesLoader : public PlayerPropertiesLoader {
public:
    JsonPlayerPropertiesLoader(std::string root_path);
};