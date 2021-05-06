//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_SF_FONT_H
#define VOYAGER_SF_FONT_H
#include "font.h"
#include <SFML/Graphics/Font.hpp>

namespace graphics::sf {
    class SfFont: public Font {
    private:
        ::sf::Font _font;
    public:
        void set_path(const std::filesystem::path &path) override;

        const ::sf::Font& get_sf_font() const;

    };
}

#endif //VOYAGER_SF_FONT_H
