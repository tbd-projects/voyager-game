#pragma once

#include "products.hpp"

class ProductsLoader {
public:
    virtual ProductBattery &load_battery(size_t cur_level) = 0;

    virtual ProductEngine &load_engine(size_t cur_level) = 0;

    virtual ProductMap &load_maps() = 0;

    virtual std::vector <ProductShip> &load_ships() = 0;

};

class JsonProductsLoader : public ProductsLoader {
public:
    JsonProductsLoader(std::string root_path);
};