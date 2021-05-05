//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H
#define VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H

#include "graphics/i_spite_loader.h"

namespace graphics::sf {

    class SfJsonSpriteSheetLoader : public ISpiteLoader {
    private:
        void _load_info();

        bool _is_loaded = false;
        std::vector<SpriteInfo> _sprites;
    public:
        SfJsonSpriteSheetLoader() = default;

        std::unique_ptr<Sprite> load(int id, TextureStorage &storage) override;

        std::unique_ptr<Sprite> load(const SpriteInfo &info, TextureStorage &storage) override;

    };
}


#endif //VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H
