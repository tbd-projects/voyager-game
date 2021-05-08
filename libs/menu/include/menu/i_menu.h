//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_I_MENU_H
#define VOYAGER_I_MENU_H

/** @todo: use external definition **/
class Event {
public:
    enum EventType {
        keyboard,
        mouse,
        fps
    };

    EventType type;

    Event(EventType type): type(type) {};

    virtual ~Event() = default;
};

#include <graphics/i_drawable.h>
class FPSEvent: public Event{
public:
    graphics::ICanvas &canvas;
    FPSEvent(graphics::ICanvas &canvas): Event(Event::fps), canvas(canvas) {}
};


class ISubscriber {
public:
    virtual void update(Event &) = 0;
};

namespace menu {
    class IMenu: public ISubscriber {
    public:
        virtual ~IMenu() = default;
    };
}


#endif //VOYAGER_I_MENU_H
