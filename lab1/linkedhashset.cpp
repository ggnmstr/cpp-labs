#include "linkedhashset.hpp"

linkedhs::linkedhs():
    capacity_(DEFAULT_CAPACITY),
    size_(0),
    arr_(new std::list<student>*[capacity_]()) {
}

linkedhs::linkedhs(const linkedhs &other):
    capacity_(other.capacity_),
    size_(other.size_),
    arr_(new std::list<student>*[capacity_]()){
        for (int i = 0; i < capacity_; i++){
            if (other.arr_[i]){
                arr_[i] = new std::list<student>;
                for (auto it = other.arr_[i]->begin(); it != other.arr_[i]->end();it++){
                    student s(*it);
                    this->arr_[i]->push_back(s);
                }
            }
        }

}

linkedhs::~linkedhs() {
    for (int i = 0; i < capacity_ ; i++){
        delete arr_[i];
    }
    delete[] arr_;
}

size_t linkedhs::size() const{
    return size_;
}

bool linkedhs::empty() const{
    return size_==0;
}

bool linkedhs::insert(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    if (arr_[hash] == nullptr){
        arr_[hash] = new std::list<student>;
    }
    std::list<student> &s1 = *arr_[hash];
    s1.push_back(e);
    size_++;
    return true;
    //arr_[]
}

bool linkedhs::remove(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    std::list<student> *list = arr_[hash];
    
    
    for (auto it = list->begin(); it != list->end(); ++it){
        if (e == *it){
            list->erase(it);
            size_--;
            return true;
        }
    }
    return false;
    
}