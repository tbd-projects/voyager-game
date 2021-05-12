//
// Created by flashie on 11.05.2021.
//
#include <filesystem>
#include <boost/property_tree/exceptions.hpp>
#include "gtest/gtest.h"
#include "exception.hpp"
#include "loaders/progress_loader.hpp"

using namespace boost::property_tree;


class BaseProgressLoaderTest : public testing::Test {
protected:
    game::BaseProgressLoader loader{};


    void SetUp() {
        auto root_dir = std::filesystem::path(
                __FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
        std::string path_load = root_dir / "libs/game/test/data/example_progress_load.json";
        this->loader = game::BaseProgressLoader{path_load};

    }

    void TearDown() {};
};

class BaseProgressSaverTest : public testing::Test {
protected:
    game::BaseProgressLoader loader{};
    game::progress_t progress;

    void SetUp() {
        auto root_dir = std::filesystem::path(
                __FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
        std::string path_save = root_dir / "libs/game/test/data/example_progress_save.json";
        this->loader = game::BaseProgressLoader{path_save};

        this->progress.time = 999;
        this->progress.coins = 999;
        for (size_t i = 0; i < 5; ++i) {
            this->progress.level_stat.push_back(std::make_pair(i, i * i));
        }
    }

    void TearDown() {};
};

TEST_F(BaseProgressLoaderTest, hasStats) {
    int player_id = 0;
    EXPECT_FALSE(this->loader.has_progress(player_id));
}

TEST_F(BaseProgressLoaderTest, noStats) {
    int player_id = 1;
    EXPECT_TRUE(this->loader.has_progress(player_id));
}

TEST_F(BaseProgressLoaderTest, statsNotFound) {
    int player_id = -1;
    EXPECT_THROW(this->loader.load(player_id), LoadError);
}

TEST_F(BaseProgressLoaderTest, statsFound) {
    int player_id = 1;
    game::progress_t progress;
    progress = this->loader.load(player_id);
    ASSERT_FALSE(progress.is_empty());
    ASSERT_EQ(progress.time, 90);
    ASSERT_EQ(progress.coins, 100);
    ASSERT_EQ(progress.level_stat.size(), 2);
}

TEST_F(BaseProgressSaverTest, statsFound) {
    int player_id = 1;
    this->loader.save(player_id, this->progress);
    game::progress_t loaded = this->loader.load(player_id);
//    ASSERT_EQ(this->progress, loaded);
}
