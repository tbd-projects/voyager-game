//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_TEXTURE_H
#define VOYAGER_I_TEXTURE_H

namespace graphics {

    class ITexture {
    public:
        virtual int get_height() = 0;
        virtual int get_width() = 0;
        virtual ~ITexture() = 0;
    };
}



#endif //VOYAGER_I_TEXTURE_H
