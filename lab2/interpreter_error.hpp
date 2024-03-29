#pragma once

#include <stdexcept>
#include <string>

class interpreter_error : public std::runtime_error {
public:
    explicit interpreter_error(const std::string &msg) : std::runtime_error(msg) {};
};