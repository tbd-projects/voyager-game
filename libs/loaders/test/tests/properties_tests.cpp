//
// Created by flashie on 09.05.2021.
//
#include <filesystem>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "loaders/properties_loader.hpp"
#include <iostream>

using namespace boost::property_tree;

auto root_dir = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
std::string prop_path = (root_dir / "data/player/example_properties.json");
std::string path_save = root_dir / "libs/loaders/test/data/example_properties_save.json";

//class MockPropertyTree : public ptree {
//public:
//    MOCK_METHOD3(read_json, void (const std::string &filename, ptree &pt, const std::locale &loc));
//    MOCK_METHOD3(write_json, void (const std::string &filename, ptree &pt, const std::locale &loc));
//};

class JsonPlayerPropertiesLoaderTest : public testing::Test {
protected:

    JsonPlayerPropertiesLoader loader{prop_path};

    void SetUp() {}

    void TearDown() {};

};

class JsonPlayerPropertiesSaverTest : public testing::Test {
protected:
    JsonPlayerPropertiesLoader loader{path_save};

    void SetUp() {}

    void TearDown() {};

};

TEST_F(JsonPlayerPropertiesLoaderTest, loadTestPlayerExist) {
    size_t player_id = 1;
    properties_t result = this->loader.load_current_properties(player_id);
    ASSERT_FALSE(result.is_empty());
    ASSERT_EQ(result.fuel, 100);
    ASSERT_EQ(result.health, 100);
    ASSERT_EQ(result.battery, 90);
    ASSERT_EQ(result.engine_power, 50);
}
TEST_F(JsonPlayerPropertiesLoaderTest, loadTestPlayerNotExist) {
    size_t player_id = -1;
    properties_t result = this->loader.load_current_properties(player_id);
    ASSERT_TRUE(result.is_empty());
}
//
//TEST(SaveTest, saveTestPlayerNotExist) {
//    int player_id = 0;
//
//    boost::property_tree::ptree test_tree;
//
//    MockPropertyTree ptree;
//
//    EXPECT_CALL(ptree, read_json(path_save, ptree, std::locale()).
//    Times(1).
//    WillOnce([&]()->void {
//        boost::property_tree::read_json(prop_path, test_tree);
//        boost::property_tree::read_json(prop_path, ptree);
//
//    }));
//
//    EXPECT_CALL(ptree, write_json(path_save, ptree, std::locale()).
//            Times(1).
//            WillOnce([&]()->void {
//        boost::property_tree::write_json(prop_path, boost::property_tree::ptree);
//    }));
//
//
//    properties_t prop{0,0,0,0};
//
//    this->loader.save_current_properties(player_id, prop);
//}
//
//
