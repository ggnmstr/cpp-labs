#include "linkedhashset.hpp"
#include <cassert>


linkedhs::linkedhs() :
        capacity_(DEFAULT_CAPACITY),
        size_(0),
        arr_(new std::list<lhsnode *>*[capacity_]()),
        head_(nullptr),
        tail_(nullptr) {
}

linkedhs::linkedhs(const linkedhs &other) :
        capacity_(other.size_ >= DEFAULT_CAPACITY * 0.5 ? other.capacity_ : DEFAULT_CAPACITY),
        size_(0),
        arr_(new std::list<lhsnode *>*[capacity_]()),
        head_(nullptr),
        tail_(nullptr) {
    // CR: replace with insert
    for (auto it = other.begin(); it != other.end(); it++) {
        element e = *it;
        this->insert(e);
    }
}

linkedhs::linkedhs(const linkedhs &other, size_t newcap) :
        capacity_(newcap),
        size_(0),
        arr_(new std::list<lhsnode *>*[newcap]()),
        head_(nullptr),
        tail_(nullptr) {
    for (auto it = other.begin(); it != other.end(); it++) {
        element e = *it;
        this->insert(e);
    }
}

linkedhs &linkedhs::operator=(const linkedhs &other) {
    if (&other == this) return *this;
    this->clear();
    linkedhs lcp(other);
    this->swap(lcp);
    return *this;
}

linkedhs::~linkedhs() {
    clear();
    delete[] arr_;
}

void linkedhs::swap(linkedhs &other) {
    size_t tmp = other.size_;
    other.size_ = size_;
    size_ = tmp;

    tmp = other.capacity_;
    other.capacity_ = capacity_;
    capacity_ = tmp;

    std::list<lhsnode *> **tmparr = other.arr_;
    other.arr_ = arr_;
    arr_ = tmparr;

    lhsnode *tmplnd = other.head_;
    other.head_ = head_;
    head_ = tmplnd;

    tmplnd = other.tail_;
    other.tail_ = tail_;
    tail_ = tmplnd;
}

void linkedhs::resize() {
    linkedhs newlhs(*this, capacity_ * 2);
    cleanl();
    swap(newlhs);
}

size_t linkedhs::size() const {
    return size_;
}

bool linkedhs::empty() const {
    return size_ == 0;
}

bool linkedhs::contains(const element &e) const {
    return find(e) != end();
}

linkedhs::iterator linkedhs::find(const element &e) const {
    unsigned long long hash = e.hash() % capacity_;
    std::list<lhsnode *> *list = arr_[hash];
    if (list == nullptr) return end();
    for (lhsnode *x: *list) {
        if (x->element_ == e) return iterator(x);
    }
    return end();
}


bool linkedhs::insert(const element &e) {
    if (this->contains(e)) return false;
    if (size_ >= capacity_ * RESIZE_FACTOR) resize();
    unsigned long long hash = e.hash();
    hash %= capacity_;
    if (arr_[hash] == nullptr){
        arr_[hash] = new std::list<lhsnode*>;
    }
    std::list<lhsnode *> *s1 = arr_[hash];
    lhsnode *newnode = new lhsnode(e, this->tail_);
    if (size_ == 0) {
        assert(this->head_ == nullptr);
        this->head_ = newnode;
    } else {
        this->tail_->next_ = newnode;
    }
    this->tail_ = newnode;
    s1->push_back(newnode);
    size_++;
    return true;
}


bool linkedhs::remove(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    std::list<lhsnode *> *list = arr_[hash];
    if (list == nullptr) return false;

    for (auto it = list->begin(); it != list->end(); ++it) {
        if (e == (*it)->element_) {
            lhsnode *cur = (*it);
            if ( cur == tail_){
                tail_ = cur->prev_;
            }
            if ( cur == head_){
                head_ = cur->next_;
            }
            if (cur->prev_ != nullptr) cur->prev_->next_ = cur->next_;
            if (cur->next_ != nullptr) cur->next_->prev_ = cur->prev_;
            list->erase(it);
            delete cur;
            size_--;
            return true;
        }
    }
    return false;

}

bool linkedhs::operator==(const linkedhs &other) const {
    if (size_ != other.size_) return false;
    for (auto it = this->begin(); it != this->end(); it++) {
        if (!(other.contains(*it))) return false;
    }
    return true;
}


bool linkedhs::operator!=(const linkedhs &other) const {
    return !(*this == other);
}


void linkedhs::clear() {
    cleanl();
    for (size_t i = 0; i < capacity_; i++){
        std::list<lhsnode *> *list = arr_[i];
        if (list == nullptr) continue;
        delete list;
        arr_[i] = nullptr;
    }
    //head_ = nullptr;
    //tail_ = nullptr;
    //assert(size_ == 0);
}

void linkedhs::cleanl() {
    for (size_t i = 0; i < capacity_; i++) {
        if (size_ == 0) break;
        std::list<lhsnode *> *list = arr_[i];
        if (list == nullptr) continue;
        for (lhsnode *x: *list) {
            delete x;
            size_--;
        }
        list->clear();

    }
    head_ = nullptr;
    tail_ = nullptr;
    assert(size_ == 0);
}


// iterator

linkedhs::iterator::iterator(lhsnode *cur) : cur_(cur) {}

linkedhs::iterator linkedhs::begin() const {
    return iterator(this->head_);
}

linkedhs::iterator linkedhs::end() const {
    return iterator(nullptr);
}

element linkedhs::iterator::operator*() {
    return cur_->element_;
}

linkedhs::iterator &linkedhs::iterator::operator--() {
    cur_ = cur_->prev_;
    return *this;
}

linkedhs::iterator linkedhs::iterator::operator--(int) {
    linkedhs::iterator it(*this);
    cur_ = cur_->prev_;
    return it;
}

linkedhs::iterator &linkedhs::iterator::operator++() {
    cur_ = cur_->next_;
    return *this;
}

linkedhs::iterator linkedhs::iterator::operator++(int) {
    linkedhs::iterator it(*this);
    cur_ = cur_->next_;
    return it;
}

bool linkedhs::iterator::operator==(const linkedhs::iterator &other) const {
    return cur_ == other.cur_;
}

bool linkedhs::iterator::operator!=(const linkedhs::iterator &other) const {
    return !(*this == other);
}