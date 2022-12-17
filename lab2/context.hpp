#pragma once

#include "datastack.hpp"
#include <sstream>

struct context {
    explicit context(datastack &stack) : stack(stack) {};
    datastack &stack;
    std::stringstream out;
};
