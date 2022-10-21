#include "linkedhashset.hpp"

// constructor of lhsnode (node of linkedhs)
lhsnode::lhsnode(student element, lhsnode *prev = nullptr, lhsnode *next = nullptr) :
        element_(element),
        next_(next),
        prev_(prev) {

}

// linkedhs default constructor
linkedhs::linkedhs() :
        capacity_(DEFAULT_CAPACITY),
        size_(0),
        arr_(new std::list<lhsnode *>[capacity_]()),
        head_(nullptr),
        tail_(nullptr) {
}

// linkedhs copy constructor
linkedhs::linkedhs(const linkedhs &other) :
        capacity_(other.capacity_),
        size_(other.size_),
        arr_(new std::list<lhsnode *>[capacity_]()) {
    for (size_t i = 0; i < capacity_; i++) {
        int c = 0;
        if (!(other.arr_[i].empty())) {
            //arr_[i] = new std::list<student>;
            for (auto it = other.arr_[i].begin(); it != other.arr_[i].end(); it++) {
                lhsnode &oldnode = **it;
                lhsnode *newnode = new lhsnode(oldnode.element_);
                if (c == 0) {
                    this->head_ = newnode;
                    this->tail_ = newnode;
                    c++;
                } else {
                    newnode->prev_ = this->tail_;
                    this->tail_->next_ = newnode;
                    this->tail_ = newnode;
                }
                this->arr_[i].push_back(newnode);
            }
        }
    }
}

// specific private copy constructor used for easier resizing 
linkedhs::linkedhs(const linkedhs &other, size_t newcap) :
        capacity_(newcap),
        size_(0),
        arr_(new std::list<lhsnode *>[newcap]()) {
    for (auto it = other.begin(); it != other.end(); it++) {
        element e = (*it);
        this->insert(e);
    }
}

// operator= 
linkedhs &linkedhs::operator=(const linkedhs &other) {
    if (&other == this) return *this;
    this->clear();
    if (other.capacity_ != capacity_) {
        delete[] arr_;
        capacity_ = other.capacity_;
        arr_ = new std::list<lhsnode *>[capacity_]();
    }
    size_ = other.size_;
    for (size_t i = 0; i < other.capacity_; i++) {
        int c = 0;
        if (!(other.arr_[i].empty())) {
            for (auto it = other.arr_[i].begin(); it != other.arr_[i].end(); it++) {
                lhsnode &oldnode = **it;
                lhsnode *newnode = new lhsnode(oldnode.element_);
                if (c == 0) {
                    this->head_ = newnode;
                    this->tail_ = newnode;
                    c++;
                } else {
                    newnode->prev_ = this->tail_;
                    this->tail_->next_ = newnode;
                    this->tail_ = newnode;
                }
                this->arr_[i].push_back(newnode);
            }
        }
    }
    return *this;
}

// destructor frees all memory allocated and empties lhs' lists
linkedhs::~linkedhs() {
    clear();
    delete[] arr_;
}

// swaps everything between 2 linkedhs'
void linkedhs::swap(linkedhs &other) {
    size_t tmp = other.size_;
    other.size_ = size_;
    size_ = tmp;

    tmp = other.capacity_;
    other.capacity_ = capacity_;
    capacity_ = tmp;

    std::list<lhsnode *> *tmparr = other.arr_;
    other.arr_ = arr_;
    arr_ = tmparr;

    lhsnode *tmplnd = other.head_;
    other.head_ = head_;
    head_ = tmplnd;

    tmplnd = other.tail_;
    other.tail_ = tail_;
    tail_ = tmplnd;
}

// private resize to 2*current capacity 
void linkedhs::resize() {
    linkedhs newlhs(*this, capacity_*2);
    clear();
    swap(newlhs);
}

// returns amount of elements added to linkedhs
size_t linkedhs::size() const {
    return size_;
}
// returns 1 if no elements were added (otherwise 0)
bool linkedhs::empty() const {
    return size_ == 0;
}

// returns 1 if element e exists in lhs
bool linkedhs::contains(const element &e) const {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    if (arr_[hash].empty()) return false;
    std::list<lhsnode *> &list = arr_[hash];
    for (lhsnode *&x: list) {
        if (x->element_ == e) return true;
    }
    return false;
}

// returns iterator pointing to element e
linkedhs::iterator linkedhs::find(const element &e) const {
    unsigned long long hash = e.hash() % capacity_;
    std::list<lhsnode*> &list = arr_[hash];
    for (lhsnode* x : list){
        if (x->element_ == e) return iterator(x);
    }
    return iterator(nullptr);
}

// inserts element e inside linkedhs 
// returns false in case of failure (element already exists)
bool linkedhs::insert(const element &e) {
    if (size_ >= capacity_ / 2) resize();
    if (this->contains(e)) return false;
    unsigned long long hash = e.hash();
    hash %= capacity_;

    std::list<lhsnode *> &s1 = arr_[hash];
    lhsnode *newnode = new lhsnode(e, this->tail_);
    if (size_ == 0) {
        this->head_ = newnode;
    } else {
        this->tail_->next_ = newnode;
    }
    this->tail_ = newnode;
    s1.push_back(newnode);
    size_++;
    return true;
}

// removes element e from lhs 
// returns false in case of failure (element not found)
bool linkedhs::remove(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    std::list<lhsnode *> &list = arr_[hash];

    for (auto it = list.begin(); it != list.end(); ++it) {
        if (e == (*it)->element_) {
            lhsnode *cur = (*it);
            if (cur->prev_ != nullptr) cur->prev_->next_ = cur->next_;
            if (cur->next_ != nullptr) cur->next_->prev_ = cur->prev_;
            list.erase(it);
            delete cur;
            size_--;
            return true;
        }
    }
    return false;

}

// comparison of every element in lhs (and also size_ and capacity_)
bool linkedhs::operator==(const linkedhs &other) const {
    if (capacity_ != other.capacity_ || size_ != other.size_) return false;
    for (auto it = this->begin(); it != this->end(); it++) {
        if (!(other.contains(*it))) return false;
    }
    return true;
}

// reverse of ==
bool linkedhs::operator!=(const linkedhs &other) const {
    return !(*this == other);
}

// frees all allocated memory and empties all lhs' lists
void linkedhs::clear() {
    for (size_t i = 0; i < capacity_; i++) {
        std::list<lhsnode *> &list = arr_[i];
        if (list.empty()) continue;
        for (lhsnode *x: list) {
            delete x;
        }
        list.clear();
    }
}

// iterator constructor
linkedhs::iterator::iterator(lhsnode *cur) : cur_(cur) {}

// returns iterator pointing to first element added to lhs
linkedhs::iterator linkedhs::begin() const {
    return iterator(this->head_);
}

// returns iterator pointing to nullptr (after last element)
linkedhs::iterator linkedhs::end() const {
    return iterator(nullptr);
}

// returns element of lhsnode
element linkedhs::iterator::operator*() {
    return cur_->element_;
}

// prefix operartor--, iterator will point to element added before element it was pointing at
linkedhs::iterator linkedhs::iterator::operator--() {
    cur_ = cur_->prev_;
    return *this;
}

// postfix operator++, iterator will point to element added after element it was pointing at
linkedhs::iterator linkedhs::iterator::operator++(int) {
    linkedhs::iterator it(*this);
    cur_ = cur_->next_;
    return it;
}

// compares if 2 iterators point at the same element (same address in memory)
bool linkedhs::iterator::operator==(const linkedhs::iterator &other) const {
    return cur_ == other.cur_;
}

// reverse of ==
bool linkedhs::iterator::operator!=(const linkedhs::iterator &other) const {
    return !(*this == other);
}