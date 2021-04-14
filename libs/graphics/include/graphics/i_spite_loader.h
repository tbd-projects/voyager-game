//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_SPITE_LOADER_H
#define VOYAGER_I_SPITE_LOADER_H

#include "graphics/texture_storage.h"
#include "graphics/i_sprite.h"

#include <memory>
namespace graphics {
    class ISpiteLoader {
    public:
        virtual std::unique_ptr<ISprite> load(int id, TextureStorage &storage) = 0;
    };
}


#endif //VOYAGER_I_SPITE_LOADER_H
