//
// Created by volodya on 14.04.2021.
//

#ifndef VOYAGER_I_DRAWABLE_H
#define VOYAGER_I_DRAWABLE_H

#include <utility>
#include <memory>

namespace graphics {

class ICanvas {
  public:
    ICanvas() = default;

    virtual ~ICanvas() = default;
};

}


#endif  // VOYAGER_I_DRAWABLE_H
