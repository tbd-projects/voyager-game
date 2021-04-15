#pragma once

#include "loaders/products_loader.hpp"

class Product {
public:
    Product(std::string name, size_t price);

    Product(ProductsLoader *loader);

    std::string get_name();

    size_t get_price();

    virtual Product &create_product() = 0;

private:
    std::string _name;
    size_t _price;
};
