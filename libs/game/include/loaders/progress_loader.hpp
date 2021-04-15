#pragma once

#include <string>

struct progress_t;

class ProgressLoader{
public:
    virtual progress_t load(int player_id) = 0;

    virtual void save(int player_id, progress_t &progress) = 0;

    virtual ~ProgressLoader() = 0;
};

class BaseProgressLoader : public ProgressLoader {
public:
    BaseProgressLoader(std::string root_path);
};