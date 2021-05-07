#pragma once

#include <iostream>

class ISprite {

};


class IGameObject {
public:
    IGameObject();

    virtual bool create_object(IGameObject &object) = 0;

    virtual bool set_sprite() = 0;

    virtual ISprite &get_sprite() = 0;

    virtual void set_sprite_id(size_t id) = 0;

    virtual ~IGameObject() = 0;

};

