#pragma once

#include <game_manager/interface.hpp>

namespace game_manager::external {

class InitLoadersForConfig : public IInitDependencies {
  public:
    InitLoadersForConfig() = default;

  protected:
    void init(Config &config) const override;
};

}  // namespace game_manager::external
