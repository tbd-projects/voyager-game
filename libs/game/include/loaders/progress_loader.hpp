#pragma once

#include <string>
#include <vector>

namespace game {

    struct progress_t {
        size_t coins;
        size_t time;
        std::vector<std::pair<int, int>> level_stat;

        bool is_empty() {
            return !coins && !time && level_stat.empty();
        }

        friend bool operator==(const progress_t &a, const progress_t &b) {
            return a.coins == b.coins && a.time == b.time;
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
        BaseProgressLoader() = default;

        ~BaseProgressLoader() override = default;

        BaseProgressLoader(const BaseProgressLoader &) = default;

        BaseProgressLoader &operator=(const BaseProgressLoader &) = default;

        explicit BaseProgressLoader(const std::string &root_path);

        progress_t load(const int player_id) override;

        void save(const int player_id, progress_t &progress) override;

        bool has_progress(const int player_id);


    private:
        std::string path;

    };
} // namespace game