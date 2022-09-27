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
    int capacity_;
    std::list<student> **arr_;
};