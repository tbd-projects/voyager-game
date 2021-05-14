//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_JSON_SPRITE_SHEET_LOADER_H
#define VOYAGER_JSON_SPRITE_SHEET_LOADER_H

#include "game_manager/imported/graphics/i_spite_loader.h"
#include "i_graphics_factory.h"

namespace graphics {

class JsonSpriteSheetLoader : public ISpiteLoader {
  public:
    explicit JsonSpriteSheetLoader(IGraphicsFactory &factory) {}
};

}


#endif   // VOYAGER_JSON_SPRITE_SHEET_LOADER_H
