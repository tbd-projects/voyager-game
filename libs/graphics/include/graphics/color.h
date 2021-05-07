//
// Created by volodya on 07.05.2021.
//

#ifndef VOYAGER_COLOR_H
#define VOYAGER_COLOR_H


struct Color {
    using byte = std::uint8_t;
    byte red = 0;
    byte green = 0;
    byte blue = 0;
    byte alpha = 255;

    Color() = default;

    Color(byte r, byte g, byte b, byte alpha = 255) :
            red(r), green(g), blue(b), alpha(alpha) {};

    explicit Color(std::tuple<byte, byte, byte> color) :
            Color(
                    std::get<0>(color),
                    std::get<1>(color),
                    std::get<2>(color)
            ) {};


    explicit Color(std::tuple<byte, byte, byte, byte> color) :
            Color(
                    std::get<0>(color),
                    std::get<1>(color),
                    std::get<2>(color),
                    std::get<3>(color)
            ) {};


};


#endif //VOYAGER_COLOR_H
