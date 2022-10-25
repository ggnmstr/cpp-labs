#pragma once

#include <list>
#include "student.hpp"

typedef student element;

// node of linkedhashset
// CR: move to private section of linkedhs class
struct lhsnode {
    student element_;
    lhsnode *next_;
    lhsnode *prev_;

    lhsnode(student element, lhsnode *prev, lhsnode *next);
};

// CR:
/*
1. definition in header
2. hasher
template<class T, class Hasher = std::hash<T>>
*/
class linkedhs {
public:
      class iterator {
    public:
        iterator(lhsnode *cur);

        element operator*();

        iterator& operator++();

        iterator operator++(int);

        iterator& operator--();

        iterator operator--(int);

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
    
    // swaps everything between 2 linkedhs'
    void swap(linkedhs &other);

    size_t size() const;

    bool empty() const;

    bool contains(const element &e) const;

    iterator find(const element &e) const;


    bool operator==(const linkedhs &other) const;

    bool operator!=(const linkedhs &other) const;

    iterator begin() const;

    iterator end() const;

    void clear();


private:
    void resize();

    linkedhs(const linkedhs &other, size_t newcap);

    static const size_t DEFAULT_CAPACITY = 128;
    // CR: static constexpr double RESIZE_COEF = 0.75
    size_t capacity_;
    size_t size_;
    // CR: store pointers to lists
      std::list<lhsnode *> *arr_;
    lhsnode *head_;
    lhsnode *tail_;
};