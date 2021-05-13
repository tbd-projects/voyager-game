//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_I_GRAPHICS_FACTORY_H
#define VOYAGER_I_GRAPHICS_FACTORY_H

#include <string>
#include <memory>

namespace graphics {

class TextureStorage;

class IGraphicsFactory {
  public:
    IGraphicsFactory() = default;

    virtual ~IGraphicsFactory() = default;
};

}  // namespace graphics

#endif  // VOYAGER_I_GRAPHICS_FACTORY_H
