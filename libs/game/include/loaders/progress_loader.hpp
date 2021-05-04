#pragma once

#include <string>

struct progress_t {
    size_t coins;
    size_t level;
    size_t stars;
    size_t time;
};

class ProgressLoader {
public:
    virtual progress_t load(const int player_id) = 0;

    virtual void save(const int player_id, progress_t &progress) = 0;

    virtual ~ProgressLoader() = 0;
};

class BaseProgressLoader : public ProgressLoader {
public:
    BaseProgressLoader() = delete;

    ~BaseProgressLoader() = default;

    BaseProgressLoader(const BaseProgressLoader &) = delete;

    BaseProgressLoader &operator=(const BaseProgressLoader &) = delete;

    explicit BaseProgressLoader(const std::string &root_path);

    progress_t load(const int player_id) override;

    void save(const int player_id, progress_t &progress) override;

private:
    std::string path;

};