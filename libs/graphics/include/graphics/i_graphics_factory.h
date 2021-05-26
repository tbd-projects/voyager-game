//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_I_GRAPHICS_FACTORY_H
#define VOYAGER_I_GRAPHICS_FACTORY_H

#include <string>
#include <memory>

#include "i_texture.h"
#include "sprite.h"
#include "font.h"
#include "sprite_info.h"
#include "text.h"
#include "rect.h"
#include "button.h"
#include "orbit_shape.h"


namespace graphics {
    class TextureStorage;
    class IGraphicsFactory {
    public:
        IGraphicsFactory() = default;

        virtual std::unique_ptr<ITexture> create_texture(const std::string &filename) = 0;

        virtual std::unique_ptr<Sprite> create_sprite(const SpriteInfo &info, TextureStorage &storage) = 0;

        virtual std::shared_ptr<Font> create_font() = 0;

        virtual std::unique_ptr<Text> create_text() = 0;

        virtual std::unique_ptr<Rect> create_rect() = 0;

        virtual std::unique_ptr<OrbitShape> create_orbit() = 0;

        virtual Button create_button() = 0;

        virtual ~IGraphicsFactory() = default;
    };

}

#endif //VOYAGER_I_GRAPHICS_FACTORY_H
