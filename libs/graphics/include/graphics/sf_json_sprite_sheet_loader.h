//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H
#define VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H

#include "graphics/i_spite_loader.h"
namespace graphics::sf {

    class SfJsonSpriteSheetLoader: public ISpiteLoader{
    public:
        std::unique_ptr<ISprite> load(int id, TextureStorage &storage) override;

    };
}


#endif //VOYAGER_SF_JSON_SPRITE_SHEET_LOADER_H
