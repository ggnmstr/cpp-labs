#pragma once
#include "datastack.hpp"
#include <sstream>

struct context {
    datastack stack;
    std::stringstream out;
};
