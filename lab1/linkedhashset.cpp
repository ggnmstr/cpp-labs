#include "linkedhashset.hpp"

linkedhs::linkedhs():
    capacity_(512), 
    arr_(new std::list<student>[capacity_]) {

}

linkedhs::~linkedhs() {
    delete[] arr_;
}

bool linkedhs::insert(const element &e) {
    long long hash = e.hash();
    hash %= capacity_;
    (arr_[hash]).push_back(e);
    return 0;
    //arr_[]
}