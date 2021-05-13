//
// Created by flashie on 13.05.2021.
//
#include <filesystem>
#include "gtest/gtest.h"
#include "loaders/level_loader.hpp"
#include "game/exceptions.hpp"


using namespace boost::property_tree;

class LevelLoader : public testing::Test {
protected:
    game::JsonCreateLevel loader;
    size_t bg_id;
    size_t cnt_planets;
    size_t cnt_stars;


    void SetUp() {
        auto root_dir = std::filesystem::path(
                __FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
        std::string path_load = root_dir / "libs/game/test/data/";
        this->loader = game::JsonCreateLevel{path_load};
        this->bg_id = 0;
        this->cnt_planets =2;
        this->cnt_stars = 2;
    }

    void TearDown() {};

};

TEST_F(LevelLoader, LevelNotFound) {
    size_t level = -1;
    EXPECT_ANY_THROW(this->loader.create_level(level));
}

TEST_F(LevelLoader, LevelFound) {
    size_t level = 1;
    EXPECT_NO_THROW(this->loader.create_level(level));
}

TEST_F(LevelLoader, LevelLoad) {
    size_t level = 1;
    EXPECT_NO_THROW(this->loader.create_level(level));
    EXPECT_EQ(this->loader.get_planets().size(), cnt_planets);
    EXPECT_EQ(this->loader.get_stars().size(), cnt_stars);
    EXPECT_EQ(this->loader.get_bg_id(), this->bg_id);
}
