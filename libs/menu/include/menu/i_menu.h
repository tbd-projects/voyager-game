//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_I_MENU_H
#define VOYAGER_I_MENU_H


#include <graphics/i_drawable.h>

/** @todo: use external definition **/
class Event {};
class ISubscriber {
public:
    virtual void update(Event) = 0;
};

namespace menu {
    class IMenu: public graphics::IDrawable, public ISubscriber {

    };
}


#endif //VOYAGER_I_MENU_H
