//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_MAIN_MENU_H
#define VOYAGER_MAIN_MENU_H

#include "menu/i_menu.h"

/** @todo import external definition **/
class ProgressLoader;
struct progress_t { int x; };

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
    class MainMenu: public IMenu {
    public:
        MainMenu();
        void draw(graphics::ICanvas &canvas) override;
        void update(Event event) override;

    private:
        ~MainMenu() override;
        Progress _progress;
    };
}

#endif //VOYAGER_MAIN_MENU_H
