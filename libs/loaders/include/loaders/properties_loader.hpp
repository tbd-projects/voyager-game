// Дмитрий Варин
#pragma once

#include <cstddef>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "math.hpp"
#include <game/interface.hpp>

namespace game::external {
class JsonPlayerPropertiesLoader : public PlayerPropertiesLoader {
public:
    JsonPlayerPropertiesLoader() = default;

    explicit JsonPlayerPropertiesLoader(const std::string &root_path);

    properties_t load_current_properties(int player_id) override;

    void save_current_properties(
            int player_id,
            properties_t &properties) override;

    bool has_player(int player_id);

protected:
    std::string path;
    size_t _sprite_id;
    std::unique_ptr<math::Polygon> _pol;
};
}  // namespace game::external

