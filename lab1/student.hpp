#include <string>

#pragma once

struct student {
        student(unsigned age, std::string name);
        bool operator==(const student &other) const;
        unsigned long long hash() const;
    private:
        friend class studentHasher;
        unsigned age_;
        std::string name_;
};

class studentHasher{
public:
    unsigned long long operator()(const student &s);
};
