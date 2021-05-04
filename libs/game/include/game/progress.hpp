//
// Created by flashie on 04.05.2021.
//

#ifndef VOYAGER_PROGRESS_HPP
#define VOYAGER_PROGRESS_HPP

#include <iostream>
#include "loaders/progress_loader.hpp"

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

#endif //VOYAGER_PROGRESS_HPP
