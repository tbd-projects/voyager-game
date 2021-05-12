//
// Created by flashie on 09.05.2021.
//
#include <filesystem>
#include "gtest/gtest.h"
#include "loaders/properties_loader.hpp"
#include "exception.hpp"
//#include "game/exceptions.hpp"

using namespace boost::property_tree;

auto root_dir = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
std::string prop_path = (root_dir / "data/player/example_properties.json");
std::string path_save = root_dir / "libs/loaders/test/data/example_properties_save.json";

class JsonPlayerPropertiesLoaderTest : public testing::Test {
protected:
    game::JsonPlayerPropertiesLoader loader{prop_path};

    void SetUp() {

    }

    void TearDown() {};

};

class JsonPlayerPropertiesSaverTest : public testing::Test {
protected:
    game::JsonPlayerPropertiesLoader loader{path_save};

};

TEST_F(JsonPlayerPropertiesLoaderTest, loadTestPlayerExist) {
    size_t player_id = 1;
    game::properties_t result = this->loader.load_current_properties(player_id);
    ASSERT_FALSE(result.is_empty());
    ASSERT_EQ(result.fuel, 100);
    ASSERT_EQ(result.health, 100);
    ASSERT_EQ(result.battery, 90);
    ASSERT_EQ(result.engine_power, 50);
}
TEST_F(JsonPlayerPropertiesLoaderTest, loadTestPlayerNotExist) {
    size_t player_id = -1;
    EXPECT_THROW(this->loader.load_current_properties(player_id), LogicError);
}
TEST_F(JsonPlayerPropertiesSaverTest, hasPropertiesPlayer) {
    int player_id = 0;
    EXPECT_TRUE(this->loader.has_player(player_id));
}
TEST_F(JsonPlayerPropertiesSaverTest, noPropertiesPlayer) {
    int player_id = 1;
    EXPECT_FALSE(this->loader.has_player(player_id));
}
TEST_F(JsonPlayerPropertiesSaverTest, saveTestPlayerNotExist) {
    int player_id = 0;

    game::properties_t prop{10,20,20,30};

    this->loader.save_current_properties(player_id, prop);

    game::properties_t prop_load;

    prop_load = this->loader.load_current_properties(player_id);

    ASSERT_EQ(prop, prop_load);

}


