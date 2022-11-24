#pragma once
#include <stack>
#include <iostream>
#include "interpreter_error.hpp"
// TODO : add * / + - mod
class Command {
    public:
        virtual void apply(std::stack<int> &stack) = 0;
        virtual ~Command() {}
};

class Plus : public Command {
    public:
        void apply(std::stack<int> &stack) override {
            if (stack.size() < 2) {
                stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int left = stack.top();
            stack.pop();
            int right = stack.top();
            stack.pop();
            stack.push(left+right);
        }
};

class Dot : public Command {
    public:
        void apply(std::stack<int> &stack) override {
            if (stack.size() < 1) {
                throw interpreter_error("Stack underflow");
            }
            int top = stack.top();
            stack.pop();
            std::cout << top << std::endl;
        }
};