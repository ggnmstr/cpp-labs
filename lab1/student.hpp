#include <string>

#pragma once

struct student {
        student(unsigned age, std::string name);
        bool operator==(const student &other) const;
    private:
        friend class studentHasher;
        unsigned age_;
        std::string name_;
};

struct studentHasher{
    size_t operator()(const student &s);
};
