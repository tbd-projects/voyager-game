#pragma once

#include <iostream>
#include <memory>

class ICanvas;
class Sprite {
public:
    void draw(ICanvas &canvas);
};

class TextureStorage {

};


class IGameObject {
public:
    IGameObject();

    virtual void set_sprite(std::unique_ptr<Sprite> sprite) = 0;

    virtual const std::unique_ptr<Sprite> &get_sprite() = 0;

    virtual void set_sprite_id(size_t id) = 0;

    virtual size_t get_sprite_id() = 0;

    virtual ~IGameObject() = 0;

protected:
    std::unique_ptr<Sprite> _sprite;
    size_t _sprite_id;
};

