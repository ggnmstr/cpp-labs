#include <string>

#pragma once

struct student {
        student(unsigned age, std::string name);
        bool operator==(const student &other) const;
        unsigned long long hash() const;
    private:
        unsigned age_;
        std::string name_;
};
