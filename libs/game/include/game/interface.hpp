#pragma once

#include <iostream>

class Sprite {

};

class TextureStorage {

};


class IGameObject {
public:
    IGameObject();

    virtual void set_sprite(Sprite *sprite) = 0;

    virtual Sprite *get_sprite() = 0;

    virtual void set_sprite_id(size_t id) = 0;

    virtual size_t get_sprite_id() = 0;

    virtual ~IGameObject() = 0;

protected:
    Sprite *_sprite;
    size_t _sprite_id;
};

