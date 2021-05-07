//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_SF_TEXT_H
#define VOYAGER_SF_TEXT_H

#include <SFML/Graphics/Text.hpp>
#include "graphics/text.h"
namespace graphics::sf {
    class SfText: public Text{
    public:
        void draw(ICanvas *canvas) override;

        void set_font(std::shared_ptr<Font> font) override;

        void set_string(const std::string &string) override;

        int get_width() override;

        void set_pos(math::coords_t pos) override;

    private:
        ::sf::Text _sf_text;
    };

}

#endif //VOYAGER_SF_TEXT_H
