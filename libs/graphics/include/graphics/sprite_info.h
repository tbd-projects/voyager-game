// Владимир Ларин
// Created by volodya on 06.05.2021.
//

#ifndef VOYAGER_SPRITE_INFO_H
#define VOYAGER_SPRITE_INFO_H
namespace graphics {
    struct SpriteInfo {
        std::pair<int, int> pos;
        std::pair<int, int> size;
        int frames;
        std::string filename;
        bool is_bg = false;
    };
}
#endif //VOYAGER_SPRITE_INFO_H
