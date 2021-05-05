//
// Created by volodya on 15.04.2021.
//


#include "graphics/sf_json_sprite_sheet_loader.h"
#include "graphics/sf_sprite.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <filesystem>

std::unique_ptr<graphics::Sprite> graphics::sf::SfJsonSpriteSheetLoader::load(int id, TextureStorage &storage) {
    if (!_is_loaded) _load_info();

    return load(_sprites[id], storage);
}

std::unique_ptr<graphics::Sprite>
graphics::sf::SfJsonSpriteSheetLoader::load(const graphics::SpriteInfo &info, graphics::TextureStorage &storage) {
    auto texture = dynamic_cast<SfTexture *> (storage.get(info.filename));
    if (info.frames == 0) {
        return std::unique_ptr<Sprite>(new SfSprite(info.pos, info.size, texture));
    }

    return std::unique_ptr<Sprite>(new SfHorizontalAnimatedSprite(info.frames, info.pos, info.size, texture));
}

void graphics::sf::SfJsonSpriteSheetLoader::_load_info() {
    _sprites.clear();
    _is_loaded = false;

    using namespace boost::property_tree;

    std::filesystem::path config_path("./libs/graphics/test/tests/sprites_info/some.json"); // @todo from config
    ptree tree;
    read_json(config_path.string(), tree);

    BOOST_FOREACH(ptree::value_type & v, tree) {
                    SpriteInfo info;
                    info.pos.first = v.second.get<int>("pos.x");
                    info.pos.second = v.second.get<int>("pos.y");

                    info.size.first = v.second.get<int>("size.x");
                    info.size.second = v.second.get<int>("size.y");

                    auto filename = v.second.get<std::string>("filename");
                    auto tpath = config_path.parent_path() / filename;
                    info.filename = tpath.string();

                    info.frames = v.second.get<int>("frames");

                    _sprites.push_back(info);
                }

    _is_loaded = true;
}
