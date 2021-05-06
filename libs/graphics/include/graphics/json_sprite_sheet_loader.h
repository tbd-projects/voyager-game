//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_JSON_SPRITE_SHEET_LOADER_H
#define VOYAGER_JSON_SPRITE_SHEET_LOADER_H

#include "graphics/i_spite_loader.h"
#include "i_graphics_factory.h"

namespace graphics {

    class JsonSpriteSheetLoader : public ISpiteLoader {
    private:
        void _load_info();

        bool _is_loaded = false;
        std::vector<SpriteInfo> _sprites;

        IGraphicsFactory &_factory;

    public:
        explicit JsonSpriteSheetLoader(IGraphicsFactory &factory);

        std::unique_ptr<Sprite> load(int id, TextureStorage &storage) override;

    };
}


#endif //VOYAGER_JSON_SPRITE_SHEET_LOADER_H
