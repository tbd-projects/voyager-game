// Владимир Ларин
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_SPITE_LOADER_H
#define VOYAGER_I_SPITE_LOADER_H

#include "graphics/texture_storage.h"
#include "graphics/sprite.h"

#include <memory>
#include "sprite_info.h"

namespace graphics {
    class ISpiteLoader {
    public:
        virtual std::unique_ptr<Sprite> load(int id, TextureStorage &storage) = 0;
    };
}


#endif //VOYAGER_I_SPITE_LOADER_H
