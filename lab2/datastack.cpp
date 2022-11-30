#include "datastack.hpp"

int datastack::top(){
    return stack_.top();
}

int datastack::pop(){
    int x = stack_.top();
    stack_.pop();
    return x;
}

void datastack::push(int x){
    stack_.push(x);
}

int datastack::size(){
    return stack_.size();
}