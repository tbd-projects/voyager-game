//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_TEXTURE_LOADER_H
#define VOYAGER_I_TEXTURE_LOADER_H

#include <memory>
#include "graphics/i_texture.h"

namespace graphics {
    class ITextureLoader {
    public:
        virtual std::unique_ptr<ITexture> load(const std::string &filename) = 0;
    };
}

#endif // VOYAGER_I_TEXTURE_LOADER_H
