// Дмитрий Варин
#pragma once

#include <string>
#include <vector>

#include <game/interface.hpp>

namespace game::external {

    class BaseProgressLoader : public ProgressLoader {
    public:
        BaseProgressLoader() = default;

        ~BaseProgressLoader() override = default;

        BaseProgressLoader(const BaseProgressLoader &) = default;

        BaseProgressLoader &operator=(const BaseProgressLoader &) = default;

        explicit BaseProgressLoader(const std::string &root_path);

        progress_t load(size_t player_id) override;

        void save(size_t player_id, progress_t &progress) override;

        bool has_progress(size_t player_id);


    private:
        std::string path;

    };
} // namespace game