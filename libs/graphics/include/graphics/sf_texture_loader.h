//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_TEXTURE_LOADER_H
#define VOYAGER_SF_TEXTURE_LOADER_H

#include <string>

#include "graphics/i_texture_loader.h"
#include "graphics/sf_texture.h"

namespace graphics::sf {

    class SfTextureLoader: public ITextureLoader{
    public:
        std::unique_ptr<ITexture> load(const std::string &filename) override;
    };
}


#endif //VOYAGER_SF_TEXTURE_LOADER_H
