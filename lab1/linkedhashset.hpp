#pragma once

#include <list>
#include "student.hpp"

typedef student element;

// node of linkedhashset
struct lhsnode {
    student element_;
    lhsnode *next_;
    lhsnode *prev_;

    lhsnode(student element, lhsnode *prev, lhsnode *next);
};


class linkedhs {
public:
    class iterator {
    public:
        iterator(lhsnode *cur);

        element operator*();

        iterator operator++(int);

        iterator operator--();

        bool operator==(const iterator &other) const;

        bool operator!=(const iterator &other) const;

    private:
        lhsnode *cur_;

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

    iterator begin() const;

    iterator end() const;

    void clear();


private:
    void resize();

    linkedhs(const linkedhs &other, size_t newcap);

    static const size_t DEFAULT_CAPACITY = 128;
    size_t capacity_;
    size_t size_;
    std::list<lhsnode *> *arr_;
    lhsnode *head_;
    lhsnode *tail_;
};