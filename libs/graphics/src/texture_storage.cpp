//
// Created by volodya on 14.04.2021.
//

#include "graphics/texture_storage.h"


namespace graphics {


    ITexture *TextureStorage::get(const std::string &filename) {
        if (_textures.find(filename) == _textures.end()) {
            load(filename);
        }
        return _textures[filename].get();
    }

    void TextureStorage::load(const std::vector<std::string> &filenames) {
        for (const auto &filename: filenames) {
            load(filename);
        }
    }

    void TextureStorage::load(const std::string &filename) {
        _textures[filename] = _loader->load(filename);
    }

    TextureStorage::TextureStorage(ITextureLoader *loader) : _loader(loader) {}
}
