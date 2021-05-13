//
// Created by volodya on 08.05.2021.
//

#ifndef VOYAGER_EVENT_H
#define VOYAGER_EVENT_H


namespace event_controller {

    enum EventType {
        keyboard,
        fps,
        close
    };

    class Event {
    public:
        EventType type;

        explicit Event(EventType type) : type(type) {};

        virtual ~Event() = default;
    };


}
#endif //VOYAGER_EVENT_H
