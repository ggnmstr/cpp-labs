#include "linkedhashset.hpp"

linkedhs::linkedhs(){
   arr_ = new int[64];
}

linkedhs::~linkedhs(){
   delete[] arr_;
}