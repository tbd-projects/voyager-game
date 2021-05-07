//
// Created by volodya on 15.04.2021.
//


#include "graphics/json_sprite_sheet_loader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <filesystem>

std::unique_ptr<graphics::Sprite> graphics::JsonSpriteSheetLoader::load(int id, TextureStorage &storage) {
    if (!_is_loaded) _load_info();

    return _factory.create_sprite(_sprites[id], storage);
}

void graphics::JsonSpriteSheetLoader::_load_info() {
    _sprites.clear();
    _is_loaded = false;

    using namespace boost::property_tree;

    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    std::filesystem::path config_path(cur_dir / "../test/tests/sprites_info/some.json");
    // @todo from config

    ptree tree;
    read_json(config_path.string(), tree);

    for (const auto& item: tree) {
        SpriteInfo info;
        info.pos.first = item.second.get<int>("pos.x");
        info.pos.second = item.second.get<int>("pos.y");

        info.size.first = item.second.get<int>("size.x");
        info.size.second = item.second.get<int>("size.y");

        auto filename = item.second.get<std::string>("filename");
        auto tpath = config_path.parent_path() / filename;
        info.filename = tpath.string();

        info.frames = item.second.get<int>("frames");

        _sprites.push_back(info);
    }
    _is_loaded = true;
}

graphics::JsonSpriteSheetLoader::JsonSpriteSheetLoader(graphics::IGraphicsFactory &factory) : _factory(factory){

}
