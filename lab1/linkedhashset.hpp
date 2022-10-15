#pragma once

#include <list>
#include "student.hpp"

typedef student element;

class linkedhs {
public:
    class iterator {
    public:
        element operator*();
        iterator operator++(int);
        iterator operator--();
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
    private:

    };


    linkedhs();

    linkedhs(const linkedhs &other);

    ~linkedhs();

    linkedhs &operator=(const linkedhs &other);

    bool insert(const element &e);

    bool remove(const element &e);

    void swap(linkedhs &other);

    size_t size() const;

    bool empty() const;

    bool contains(const element &e) const;

    bool operator==(const linkedhs &other) const;

    bool operator!=(const linkedhs &other) const;


    void clear();

private:
    static const size_t DEFAULT_CAPACITY = 1;
    size_t capacity_;
    size_t size_;
    std::list<student> **arr_;
    //std::list<student*> added_;
};