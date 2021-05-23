//
// Created by volodya on 24.05.2021.
//

#include <menu/game_screen.h>

void menu::GameScreen::draw(graphics::ICanvas *canvas) {
    if (!_screen_width)
        set_screen_width(canvas->get_width());

    _battery_text->draw(canvas);
    _timer_text->draw(canvas);
    _fuel_text->draw(canvas);

    _fuel_icon->draw(canvas);
    _battery_icon->draw(canvas);
}

menu::GameScreen::GameScreen(graphics::IGraphicsFactory &factory, graphics::ISpiteLoader &loader,
                             graphics::TextureStorage &storage,
                             int screen_width) : _screen_width(screen_width), _factory(factory), _loader(loader),
                                                                  _storage(storage) {

    _battery_icon = _loader.load(2, _storage);
    _fuel_icon = _loader.load(3, _storage);

    int h = _battery_icon->get_texture_size().second * 0.7;

    auto font = _factory.create_font();
    auto cur_dir = std::filesystem::path(__FILE__).parent_path();
    font->set_path(cur_dir / "../../graphics/test/tests/fonts/Roboto-Medium.ttf");

    _battery_text = _factory.create_text();
    _timer_text = _factory.create_text();
    _fuel_text = _factory.create_text();

    _battery_text->set_font(font);
    _timer_text->set_font(font);
    _fuel_text->set_font(font);


    _battery_text->set_size(h);
    _timer_text->set_size(h);
    _fuel_text->set_size(h);

    auto color = Color(255, 255, 255);
    _battery_text->set_color(color);
    _timer_text->set_color(color);
    _fuel_text->set_color(color);
}

void menu::GameScreen::update(int timer, int fuel, int battery) {

    int m = timer / 60;
    int s = timer % 60;

    auto time_str = std::to_string(m) + ":";
    if (s < 10) time_str += "0";
    time_str += std::to_string(s);

    _timer_text->set_string(time_str);
    _fuel_text->set_string(std::to_string(fuel));
    _battery_text->set_string(std::to_string(battery));

    _recount_positions();

}

void menu::GameScreen::_recount_positions() {
    auto w = _screen_width;

    math::decimal_t pos_y = _battery_icon->get_texture_size().second;
    math::decimal_t pos_x = w - _timer_text->get_width() / 2. - 20;

    _timer_text->set_pos(math::coords_t(pos_x, pos_y));
    pos_x = _battery_icon->get_texture_size().second / 2 + 20;
    _battery_icon->set_pos(math::coords_t(pos_x, pos_y));

    pos_x += + _battery_icon->get_texture_size().second / 2 + _battery_text->get_width() / 2. + 10;
    _battery_text->set_pos(math::coords_t(pos_x, pos_y));

    pos_x += _battery_text->get_width() / 2. + _fuel_icon->get_texture_size().second / 2 + 20;
    _fuel_icon->set_pos(math::coords_t(pos_x, pos_y));

    pos_x += _fuel_icon->get_texture_size().second / 2 + _fuel_text->get_width() / 2. + 10;
    _fuel_text->set_pos(math::coords_t(pos_x, pos_y));
}

void menu::GameScreen::set_screen_width(int width) {
    _screen_width = width;
    _recount_positions();
}
