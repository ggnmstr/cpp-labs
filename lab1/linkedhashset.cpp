#include "linkedhashset.hpp"

linkedhs::linkedhs() {
    arr_ = new std::list<student>[512];
}

linkedhs::~linkedhs() {
    delete[] arr_;
}

bool linkedhs::insert(const int &e) {

}