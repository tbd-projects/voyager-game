// Владимир Ларин
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_FONT_H
#define VOYAGER_FONT_H

#include <filesystem>
#include <string>

#include "color.h"

namespace graphics {
    class Font {
    private:
        std::filesystem::path _path;
    public:
        Font() = default;
        explicit Font(const std::string& path);
        explicit Font(const std::filesystem::path& path);

        virtual std::filesystem::path get_path() const;

        virtual void set_path(const std::filesystem::path &path);

        virtual ~Font() = default;
    };
}


#endif //VOYAGER_FONT_H
