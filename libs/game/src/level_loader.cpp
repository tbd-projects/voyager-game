#include "loaders/level_loader.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "debug/exception.h"
#include "objects.hpp"

JsonCreateLevel::JsonCreateLevel(std::string path) {
    if (path.empty()) {
        throw InvalidArg(__FILE__, typeid(*this).name(), __FUNCTION__);
    }
    this->_path = path;
}

void JsonCreateLevel::create_level() {

    pt::ptree tree;
    pt::read_json(this->_path, tree);
    size_t background_id = tree.get<size_t>("background.sprite_id");
//    this->_level_texture = new ISprite(background_id);

    this->load_space_object(tree, "stars");
    this->load_space_object(tree, "planets");




}

IGameObject *JsonCreateLevel::load_space_object(pt::ptree& tree, std::string obj_name) {
    for (pt::ptree::value_type &planet : tree.get_child(obj_name)) {
        size_t x_c = planet.second.get<size_t>("x_c");
        size_t y_c = planet.second.get<size_t>("y_c");
        size_t a = planet.second.get<size_t>("a");
        size_t b = planet.second.get<size_t>("b");

        size_t sprite_id = planet.second.get<size_t>("sprite_id");


    }
}


void JsonCreateLevel::create_ship() {

}

void JsonCreateLevel::create_objects() {

}