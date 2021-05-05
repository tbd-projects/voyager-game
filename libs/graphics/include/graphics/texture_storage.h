//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_TEXTURE_STORAGE_H
#define VOYAGER_TEXTURE_STORAGE_H

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "graphics/i_texture.h"
#include "graphics/i_texture_loader.h"


namespace graphics {
    class TextureStorage {
    public:

        explicit TextureStorage(ITextureLoader *loader);

        ITexture *get(const std::string &filename);

        void load(const std::vector<std::string> &filenames);

        void load(const std::string &filename);

    private:
        std::map<std::string, std::unique_ptr<ITexture>> _textures;
        ITextureLoader *_loader;
    };

}

#endif //VOYAGER_TEXTURE_STORAGE_H
