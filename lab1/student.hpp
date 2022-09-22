#include <string>

#pragma once

struct student {
    student(unsigned age, std::string name);
    bool operator==(const student &other) const;
    long long hash() const;
    unsigned age_;
    std::string name_;
};
