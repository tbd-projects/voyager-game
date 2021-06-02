#pragma once

#include "base_product.hpp"

class ISprite;

class ProductShip : public Product {
private:
    SpaceShip _ship;
};

class ProductBattery : public Product {
private:
    size_t _battery;
public:
    size_t get_battery();
};

class ProductEngine : public Product {
private:
    size_t _engine;
public:
    size_t get_engine();
};

class ProductMap : public Product {
private:
    std::vector <ISprite*> _maps;
public:
    ISprite &get_texture(size_t id);
};
