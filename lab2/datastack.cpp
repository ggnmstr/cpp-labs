#include "datastack.hpp"
#include "interpreter_error.hpp"

int datastack::top() {
    if (stack_.empty()) throw interpreter_error("Stack underflow");
    return stack_.top();
}

int datastack::pop() {
    if (stack_.empty()) throw interpreter_error("Stack underflow");
    int x = stack_.top();
    stack_.pop();
    return x;
}

void datastack::push(int x) {
    stack_.push(x);
}