//
// Created by volodya on 14.04.2021.
//

#include "graphics/texture_storage.h"



namespace graphics {


   ITexture *TextureStorage::get(const std::string &filename) {
        return _textures["some"].get();
    }

    void TextureStorage::load(const std::vector<std::string> &filenames) {

    }
}
