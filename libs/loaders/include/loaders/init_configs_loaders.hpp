#include <game_manager/interface.hpp>

namespace game_manager::imported {

class InitLoadersForConfig : public IInitImportImplForConfig {
  public:
    InitLoadersForConfig() = default;

  protected:
    void init(Config &config) const override;
};

}  // namespace game_manager::imported
