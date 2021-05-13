//
// Created by volodya on 07.05.2021.
//

#ifndef VOYAGER_BUTTON_H
#define VOYAGER_BUTTON_H

#include "rect.h"
#include "text.h"

namespace graphics {
    class Button : public IDrawable, public math::RectanglePolygon {

    public:
        Button(Rect *rect, Text *text);

        [[nodiscard]] int get_padding() const;

        void set_padding(int padding);

        void draw(ICanvas *canvas) override;

        void set_rotation(math::decimal_t angle) override;

        void resize(math::decimal_t height, math::decimal_t width);

        void scale(math::decimal_t scale) override;

        void set_pos(math::coords_t pos) override;

        [[nodiscard]] bool is_focused() const;

        void set_focus(bool focused = true);

        [[nodiscard]] const Color &get_focus_text_color() const;

        void set_focus_text_color(const Color &color);

        [[nodiscard]] const Color &get_focus_bg_color() const;

        void set_focus_bg_color(const Color &color);

        [[nodiscard]] const Color &get_text_color() const;

        void set_text_color(const Color &color);

        [[nodiscard]] const Color &get_bg_color() const;

        void set_bg_color(const Color &color);

        void set_string(const std::string& string);

        void set_font(std::shared_ptr<Font> font);

    private:
        void _update_drawables();

        std::unique_ptr<Rect> _rect;
        std::unique_ptr<Text> _text;

        int _padding = 0;
        bool _is_focused = false;

        Color _focus_text_color = Color(0, 0, 0);
        Color _focus_bg_color = Color(255, 255, 255);

        Color _text_color = Color(255, 255, 255);
        Color _bg_color = Color(255, 0, 0);
    };

}

#endif //VOYAGER_BUTTON_H
