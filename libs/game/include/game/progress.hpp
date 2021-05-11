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

        progress_t &set_progress(progress_t &progress);

    private:
        progress_t _progress;

    };
}

