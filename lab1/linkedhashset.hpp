#pragma once

#include <list>
#include "student.hpp"
typedef student element;
class linkedhs {
public:
    linkedhs();
    ~linkedhs();

    bool insert(const element &e);
    bool remove(const element &e);

private:
    std::list <student> *arr_;
    int capacity_;
};