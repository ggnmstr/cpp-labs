#pragma once
#include <cassert>
#include "linkedhashset.h"

template<class T, class Hasher>
linkedhs<T,Hasher>::linkedhs() :
        capacity_(DEFAULT_CAPACITY),
        size_(0),
        arr_(new std::list<lhsnode *>*[capacity_]()),
        head_(nullptr),
        tail_(nullptr) {
}

template<class T, class Hasher>
linkedhs<T,Hasher>::linkedhs(const linkedhs<T,Hasher> &other) :
    linkedhs(other,needs_resize(other.size_,DEFAULT_CAPACITY) ? other.capacity_ : DEFAULT_CAPACITY) {
}

template<class T, class Hasher>
linkedhs<T,Hasher>::linkedhs(const linkedhs<T,Hasher> &other, size_t newcap) :
        capacity_(newcap),
        size_(0),
        arr_(new std::list<lhsnode *>*[newcap]()),
        head_(nullptr),
        tail_(nullptr) {
    for (const T & e : other) {
        this->insert(e);
    }
}

template<class T, class Hasher>
linkedhs<T,Hasher> &linkedhs<T,Hasher>::operator=(linkedhs<T,Hasher> other) {
    this->swap(other);
    return *this;
}

template<class T, class Hasher>
linkedhs<T,Hasher>::~linkedhs() {
    this->clear();
    delete[] this->arr_;
}

template<class T, class Hasher>
void linkedhs<T,Hasher>::swap(linkedhs<T,Hasher> &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_,other.capacity_);
    std::swap(this->arr_, other.arr_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
}

template<class T, class Hasher>
void linkedhs<T,Hasher>::resize() {
    linkedhs<T,Hasher> newlhs(*this, this->capacity_ * 2);
    this->swap(newlhs);
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::needs_resize(size_t size, size_t cap) const{
    return size >= cap * RESIZE_FACTOR;
}

template<class T, class Hasher>
size_t linkedhs<T,Hasher>::size() const {
    return this->size_;
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::empty() const {
    return this->size_ == 0;
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::contains(const T &e) const {
    return this->find(e) != this->end();
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator linkedhs<T,Hasher>::find(const T &e) const {
    std::list<lhsnode *> *list = this->get_list(e);
    if (list == nullptr) return this->end();
    auto it = std::find_if(list->begin(), list->end(), [&e](lhsnode * x){ return x->element_ == e; });
    return it == list->end() ? this->end() : iterator(*it);
}


template<class T, class Hasher>
bool linkedhs<T,Hasher>::insert(const T &e) {
    if (this->contains(e)) return false;
    if (this->needs_resize(size_,capacity_)) this->resize();
    size_t hash = Hasher()(e);
    hash %= capacity_;
    if (this->arr_[hash] == nullptr) this->arr_[hash] = new std::list<lhsnode*>;
    std::list<lhsnode *> *s1 = this->arr_[hash];
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

template<class T, class Hasher>
bool linkedhs<T,Hasher>::remove(const T &e) {
    std::list<lhsnode *> *list = this->get_list(e);
    if (list == nullptr) return false;

    for (auto it = list->begin(); it != list->end(); ++it) {
        if (e == (*it)->element_) {
            lhsnode *cur = (*it);
            if ( cur == tail_) this->tail_ = cur->prev_;
            if ( cur == head_) this->head_ = cur->next_;

            if (cur->prev_ != nullptr) cur->prev_->next_ = cur->next_;
            if (cur->next_ != nullptr) cur->next_->prev_ = cur->prev_;
            list->erase(it);
            delete cur;
            this->size_--;
            return true;
        }
    }
    return false;

}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::operator==(const linkedhs<T,Hasher> &other) const {
    if (this->size_ != other.size_) return false;
    for (auto it = this->begin(); it != this->end(); it++) {
        if (!(other.contains(*it))) return false;
    }
    return true;
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::operator!=(const linkedhs<T,Hasher> &other) const {
    return !(*this == other);
}

template<class T, class Hasher>
void linkedhs<T,Hasher>::clear() {
    this->clear_lists();
    for (size_t i = 0; i < capacity_; i++){
        std::list<lhsnode *> *list = arr_[i];
        if (list == nullptr) continue;
        delete list;
        arr_[i] = nullptr;
    }
}

template<class T, class Hasher>
void linkedhs<T,Hasher>::clear_lists() {
    for (size_t i = 0; i < this->capacity_; i++) {
        if (this->size_ == 0) break;
        std::list<lhsnode *> *list = this->arr_[i];
        if (list == nullptr) continue;
        for (lhsnode *x: *list) {
            delete x;
            this->size_--;
        }
        list->clear();

    }
    this->head_ = nullptr;
    this->tail_ = nullptr;
    assert(this->size_ == 0);
}

// iterator
template<class T, class Hasher>
linkedhs<T,Hasher>::iterator::iterator(lhsnode *cur) : cur_(cur) {}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator linkedhs<T,Hasher>::begin() const {
    return iterator(this->head_);
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator linkedhs<T,Hasher>::end() const {
    return iterator(nullptr);
}

template<typename T, typename Hasher>
typename std::list<typename linkedhs<T, Hasher>::lhsnode *> * linkedhs<T, Hasher>::get_list(const T &e) const {
    size_t hash = Hasher()(e);
    hash %= capacity_;
    std::list<lhsnode *> *list = arr_[hash];
    return list;
}

template<class T, class Hasher>
T linkedhs<T,Hasher>::iterator::operator*() {
    return this->cur_->element_;
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator &linkedhs<T,Hasher>::iterator::operator--() {
    this->cur_ = cur_->prev_;
    return *this;
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator linkedhs<T,Hasher>::iterator::operator--(int) {
    linkedhs<T,Hasher>::iterator it(*this);
    this->cur_ = cur_->prev_;
    return it;
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator &linkedhs<T,Hasher>::iterator::operator++() {
    this->cur_ = cur_->next_;
    return *this;
}

template<class T, class Hasher>
typename linkedhs<T,Hasher>::iterator linkedhs<T,Hasher>::iterator::operator++(int) {
    linkedhs<T,Hasher>::iterator it(*this);
    this->cur_ = cur_->next_;
    return it;
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::iterator::operator==(const linkedhs<T,Hasher>::iterator &other) const {
    return this->cur_ == other.cur_;
}

template<class T, class Hasher>
bool linkedhs<T,Hasher>::iterator::operator!=(const linkedhs<T,Hasher>::iterator &other) const {
    return !(*this == other);
}
