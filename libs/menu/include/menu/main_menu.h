//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_MAIN_MENU_H
#define VOYAGER_MAIN_MENU_H

#include "graphics/i_graphics_factory.h"
#include "graphics/texture_storage.h"
#include "menu/vertical_centered_menu.h"

/** @todo import external definition **/
class ProgressLoader;

struct progress_t {
    int x;
};

class Progress {
public:
    Progress() = delete;

    Progress(ProgressLoader *loader) {};

//    Progress(const progress_t &progress) {};
//    Progress& operator=(const Progress& progress) {};
    ~Progress() = default;
//    progress_t &get_progress();
//    progress_t &set_progress(progress_t &progress);
private:
    progress_t _progress;
};

namespace menu {
    class MainMenu : public VerticalCenteredMenu {
    public:
        MainMenu(graphics::IGraphicsFactory &factory);

        void update(Event &event) override;


        ~MainMenu() override;

    private:
        graphics::IGraphicsFactory &_factory;

        std::unique_ptr<graphics::Sprite> _bg;

        graphics::TextureStorage _storage;

        Progress _progress;

        static menu::CommandButton
        _create_button(graphics::IGraphicsFactory &factory, std::shared_ptr<graphics::Font> &font,
                       std::unique_ptr<ICommand> &&command, const std::string &title);
    };
}

#endif //VOYAGER_MAIN_MENU_H
