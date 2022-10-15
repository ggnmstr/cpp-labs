#pragma once

#include <list>
#include "student.hpp"
typedef student element;
class linkedhs {
public:
    linkedhs();
    linkedhs(const linkedhs &other);
    ~linkedhs();
    linkedhs & operator=(const linkedhs & other);

    bool insert(const element &e);
    bool remove(const element &e);

    void swap(linkedhs &other);

    size_t size() const;
    bool empty() const;

    bool contains(const element & e) const;

    bool operator==(const linkedhs & other) const;
    bool operator!=(const linkedhs & other) const;



    void clear();

private:
    static const int DEFAULT_CAPACITY = 1;
    int capacity_;
    size_t size_;
    std::list<student> **arr_;
};