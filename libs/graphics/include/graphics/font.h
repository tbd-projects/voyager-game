//
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_FONT_H
#define VOYAGER_FONT_H

#include <filesystem>
#include <string>

namespace graphics {
    class Font {
    private:
        std::filesystem::path _path;
        int _size = 16;
        std::tuple<char, char, char> _color = std::tuple<char, char, char>(0, 0, 0);
    public:
        Font() = default;
        explicit Font(const std::string& path);
        explicit Font(const std::filesystem::path& path);

        virtual std::filesystem::path get_path() const;

        virtual void set_path(const std::filesystem::path &path);

        virtual int get_size() const;

        virtual void set_size(int size);

        virtual std::tuple<char, char, char> get_color() const;

        virtual void set_color(const std::tuple<char, char, char> &color);

        virtual ~Font() = default;
    };
}


#endif //VOYAGER_FONT_H
