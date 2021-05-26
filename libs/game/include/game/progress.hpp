//
// Created by flashie on 04.05.2021.
//

#pragma once

#include <iostream>
#include "loaders/progress_loader.hpp"
namespace game {

    class Progress {
    public:
        Progress() = default;

        explicit Progress(ProgressLoader *loader);

        explicit Progress(const progress_t &progress);

        Progress &operator=(const Progress &progress);

        ~Progress() = default;

        progress_t &get_progress();

        const level_stat &get_level_stat(unsigned int level_num);

        void update_level(unsigned int level_num, level_stat progress);

        progress_t &set_progress(progress_t &progress);

    private:
        progress_t _progress;

    };
}

