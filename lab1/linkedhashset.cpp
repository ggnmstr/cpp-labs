#include "linkedhashset.hpp"

linkedhs::linkedhs():
    capacity_(512),
    arr_(new std::list<student>*[capacity_]()) {
}

linkedhs::~linkedhs() {
    for (int i = 0; i < capacity_ ; i++){
        delete arr_[i];
    }
    delete[] arr_;
}

bool linkedhs::insert(const element &e) {
    unsigned long long hash = e.hash();
    hash %= capacity_;
    if (arr_[hash] == nullptr){
        arr_[hash] = new std::list<student>;
    }
    arr_[hash]->push_back(e);
    return 0;
    //arr_[]
}