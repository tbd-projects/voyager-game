// Дмитрий Варин
//
// Created by flashie on 04.05.2021.
//
#include <game_manager/config.hpp>
#include "progress.hpp"
#include "debug/exception.hpp"

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

[[maybe_unused]] progress_t &Progress::set_progress(progress_t &progress) {
        this->_progress = progress;
        return progress;
    }

    const level_stat &Progress::get_level_stat(unsigned int level_num) {
        if (level_num > game_manager::Config::get_instance() \
                        .levels_loader->get_levels_count()) {
            throw debug::INVALID_ARG_ERROR();
        }
        ssize_t num_of_struct = -1;
        for (size_t i = 0; i < _progress.levels.size(); ++i) {
            if (_progress.levels[i].num == level_num) {
                num_of_struct = i;
                break;
            }
        }
        if (num_of_struct == -1) {
            throw debug::LogicError(
                    __FILE__,
                    typeid(*this).name(),
                    __FUNCTION__);
        } else {
            return _progress.levels[num_of_struct];
        }
    }

    void Progress::update_level(unsigned int level_num, level_stat progress) {
        if (level_num > game_manager::Config::get_instance() \
.levels_loader->get_levels_count()) {
            throw debug::INVALID_ARG_ERROR();
        }
        ssize_t num_of_struct = -1;
        for (size_t i = 0; i < _progress.levels.size(); ++i) {
            if (_progress.levels[i].num == level_num) {
                num_of_struct = i;
                break;
            }
        }
        if (num_of_struct == -1) {
            _progress.levels.push_back(progress);
        } else {
            _progress.levels[num_of_struct] = progress;
        }
    }
}  // namespace game

