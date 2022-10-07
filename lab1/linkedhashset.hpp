#pragma once

#include <list>
#include "student.hpp"
typedef student element;
class linkedhs {
public:
    linkedhs();
    linkedhs(const linkedhs &other);
    ~linkedhs();

    size_t size() const;
    bool empty() const;


    bool insert(const element &e);
    bool remove(const element &e);

private:
    static const int DEFAULT_CAPACITY = 512;
    int capacity_;
    size_t size_;
    std::list<student> **arr_;
};