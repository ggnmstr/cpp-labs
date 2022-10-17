#include "linkedhashset.hpp"


lhsnode::lhsnode(student element, lhsnode *next = nullptr, lhsnode *prev = nullptr) :
        element_(element),
        next_(next),
        prev_(prev) {

}

linkedhs::linkedhs() :
        capacity_(DEFAULT_CAPACITY),
        size_(0),
        arr_(new std::list<student> *[capacity_]()) {
}

linkedhs::linkedhs(const linkedhs &other) :
        capacity_(other.capacity_),
        size_(other.size_),
        arr_(new std::list<student> *[capacity_]()) {
    for (size_t i = 0; i < capacity_; i++) {
        if (other.arr_[i]) {
            arr_[i] = new std::list<student>;
            for (auto it = other.arr_[i]->begin(); it != other.arr_[i]->end(); it++) {
                student s(*it);
                this->arr_[i]->push_back(s);
            }
        }
    }
}

linkedhs &linkedhs::operator=(const linkedhs &other) {
    this->clear();
    if (other.capacity_ != capacity_) {
        delete[] arr_;
        capacity_ = other.capacity_;
        arr_ = new std::list<student> *[capacity_]();
    }
    size_ = other.size_;
    for (size_t i = 0; i < other.capacity_; i++) {
        if (other.arr_[i]) {
            arr_[i] = new std::list<student>;
            for (auto it = other.arr_[i]->begin(); it != other.arr_[i]->end(); it++) {
                student s(*it);
                this->arr_[i]->push_back(s);
            }
        }
    }
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

    std::list<student> **tmparr = other.arr_;
    other.arr_ = arr_;
    arr_ = tmparr;
}


size_t linkedhs::size() const {
    return size_;
}

bool linkedhs::empty() const {
    return size_ == 0;
}

bool linkedhs::contains(const element &e) const {
    unsigned long long hash = e.hash();
    if (arr_[hash] == nullptr) return false;
    std::list<student> &list = *arr_[hash];
    for (student &x: list) {
        if (x == e) return true;
    }
    return false;
}

bool linkedhs::insert(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    if (arr_[hash] == nullptr) {
        arr_[hash] = new std::list<student>;
    }
    std::list<student> &s1 = *arr_[hash];
    //push_back creates the copy of e
    s1.push_back(e);
    student *p = &s1.back();
    size_++;
    added_.push_back(p);
    return true;
}

bool linkedhs::remove(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    std::list<student> *list = arr_[hash];


    for (auto it = list->begin(); it != list->end(); ++it) {
        if (e == *it) {
            added_.remove(&(*it));
            list->erase(it);
            size_--;
            return true;
        }
    }
    return false;

}

bool linkedhs::operator==(const linkedhs &other) const {
    if (capacity_ != other.capacity_ || size_ != other.size_) return false;
    //todo : rewrite the following code so it only uses iterator and contains()
    for (size_t i = 0; i < capacity_; i++) {
        if (arr_[i] != nullptr && other.arr_[i] == nullptr) return false;
        if (arr_[i] == nullptr && other.arr_[i] == nullptr) continue;
        //std::list<student> &tlist = *arr_[i];
        //std::list<student> &olist = *other.arr_[i];
        //todo : compare this 2 lists so they contain the same elements
    }
    return true;
}

bool linkedhs::operator!=(const linkedhs &other) const {
    return !(*this == other);
}


void linkedhs::clear() {
    for (size_t i = 0; i < capacity_; i++) {
        delete arr_[i];
    }
}