#pragma once

#include "products.hpp"
#include "loaders/progress_loader.hpp"
#include "loaders/properties_loader.hpp"
#include "products_loader.hpp"


class Shop {
public:
    Shop();

    Shop(Properties &properties);

    ~Shop();


    SpaceShip &buy_ship(size_t num);

    size_t buy_battery();

    size_t buy_engine();

    size_t buy_map();

private:
    std::vector <ProductShip> _ships;
    ProductBattery _battery;
    ProductEngine _engine;
    std::vector <Textures> _maps_bg;

    void fill_store(PlayerProperiesLoader *loader_properties, BaseProgressLoader *loader_progress);
};