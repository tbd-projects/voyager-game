#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

namespace game {

class CreatorLevel {
  public:
    virtual void create_level(size_t level_num) = 0;

    virtual ~CreatorLevel() = default;
};

class JsonCreateLevel : public CreatorLevel {
  public:
    JsonCreateLevel() = delete;

    explicit JsonCreateLevel(std::string level_dir) {}

    void create_level(size_t level_num) override {}
};

}  // namespace game
