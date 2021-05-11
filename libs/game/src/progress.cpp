//
// Created by flashie on 04.05.2021.
//
#include "progress.hpp"

namespace game {
    Progress::Progress(ProgressLoader *loader) {
        if (!loader) {
            throw std::invalid_argument("ProgressLoader ptr invalid");
        }
    }

    Progress::Progress(const progress_t &progress) {
        this->_progress = progress;
    }

    Progress &Progress::operator=(const Progress &progress) {
        if (&progress != this) {
            Progress tmp(progress);
            std::swap(this->_progress, tmp._progress);
        }
        return *this;
    }

    progress_t &Progress::get_progress() {
        return this->_progress;
    }

    progress_t &Progress::set_progress(progress_t &progress) {
        this->_progress = progress;
        return progress;
    }
} // namespace game
