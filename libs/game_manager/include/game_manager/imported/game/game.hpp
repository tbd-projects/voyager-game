#pragma once

#include <cstddef>
#include <vector>

#include "loaders/level_loader.hpp"
#include "imported/event_controller/i_controller.h"

class Game {
public:
    explicit Game(event_controller::IController *controller)  {}
};
