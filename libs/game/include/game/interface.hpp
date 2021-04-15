#pragma once

using coords_t = std::pair<int, int>;

class ISprite;
class Collision;


class IGameObject : {
public:
    IGameObject();

    bool check_collision(const Collision &collision);

    virtual bool create_object(IGameObject &object) = 0;

    virtual void move(coords_t coords) = 0;

    virtual bool set_sprite() = 0;

    virtual ISprite &get_sprite() = 0;

    virtual set_sprite_id(size_t
    id) = 0;

    ~IGameObject() = default;

private:
    virtual set_object_collision() = 0;
};

