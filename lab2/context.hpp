#pragma once

#include "datastack.hpp"
#include <sstream>

struct context {
    context(datastack &stack) : stack(stack) {};
    datastack &stack;
    std::stringstream out;
};
