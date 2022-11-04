#pragma once
#include <list>
#include <functional>

template<typename T, typename Hasher = std::hash<T>>
class linkedhs {
private:
    struct lhsnode;
public:
    class iterator {
    public:
        // iterator constructor
        explicit iterator(lhsnode *cur);

        // returns element of lhsnode
        T operator*();

        // prefix operator++, iterator will point to element added after element it was pointing at
        iterator &operator++();

        // postfix operator++, iterator will point to element added after element it was pointing at
        iterator operator++(int);

        // prefix operartor--, iterator will point to element added before element it was pointing at
        iterator &operator--();

        // postfix operartor--, iterator will point to element added before element it was pointing at
        iterator operator--(int);

        // compares if 2 iterators point at the same element (same address in memory)
        bool operator==(const iterator &other) const;

        // reverse of ==
        bool operator!=(const iterator &other) const;

    private:
        linkedhs::lhsnode *cur_;
    };

    // linkedhs default constructor
    linkedhs();

    // linkedhs copy constructor
    linkedhs(const linkedhs &other);

    // destructor frees all memory allocated and empties lhs' lists
    ~linkedhs();

    // operator=
    linkedhs &operator=(linkedhs other);

    // inserts element e inside linkedhs
    // returns false in case of failure (element already exists)
    bool insert(const T &e);

    // removes element e from lhs
    // returns false in case of failure (element not found)
    bool remove(const T &e);

    // swaps everything between 2 linkedhs'
    void swap(linkedhs &other);

    // returns amount of elements added to linkedhs
    size_t size() const;

    // returns true if no elements were added (otherwise false)
    bool empty() const;

    // returns true if element e exists in lhs
    bool contains(const T &e) const;

    // returns iterator pointing to element e
    iterator find(const T &e) const;

    // comparison of every element in lhs (and also size_)
    bool operator==(const linkedhs &other) const;

    // reverse of ==
    bool operator!=(const linkedhs &other) const;

    // returns iterator pointing to first element added to lhs
    iterator begin() const;

    // returns iterator pointing to nullptr (after last element)
    iterator end() const;

    // frees all allocated memory and empties all lhs' lists
    void clear();


private:

    bool needs_resize(size_t size, size_t cap) const;

    // node of linkedhashset
    struct lhsnode {
        T element_;
        lhsnode *next_;
        lhsnode *prev_;

        // constructor of lhsnode (node of linkedhs)
        explicit lhsnode(T element, lhsnode *prev = nullptr, lhsnode *next = nullptr) :
                element_(element),
                next_(next),
                prev_(prev) {

        }
    };

    typename std::list<lhsnode*>* get_list(const T &e) const;

    friend linkedhs::iterator;

    // private resize to 2*current capacity
    void resize();

    // this clean method doesn't delete pointers to std::list<lhsnode*>
    void clear_lists();

    // specific private copy constructor used for easier resizing
    linkedhs(const linkedhs &other, size_t newcap);

    static constexpr double RESIZE_FACTOR = 0.75;

    static const size_t DEFAULT_CAPACITY = 128;

    size_t capacity_;
    size_t size_;
    
    std::list<lhsnode *> **arr_;
    lhsnode *head_;
    lhsnode *tail_;
};
