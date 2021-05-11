#pragma once

#include <string>
#include <vector>

struct progress_t {
    size_t coins;
    size_t time;
    std::vector<std::pair<int, int>> level_stat;

    bool is_empty() {
        return !coins && !time && level_stat.empty();
    }
};

class ProgressLoader {
public:
    virtual progress_t load(const int player_id) = 0;

    virtual void save(const int player_id, progress_t &progress) = 0;

    virtual ~ProgressLoader() = default;
};

class BaseProgressLoader : public ProgressLoader {
  public:
    explicit BaseProgressLoader(const std::string &root_path) {}

    progress_t load(const int player_id) override {return {};}

    void save(const int player_id, progress_t &progress) override {}

  private:
    std::string path;
};
