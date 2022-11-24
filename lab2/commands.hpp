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
            int size = stack.size();
            if (size == 0) throw interpreter_error("Stack underflow");
            if (size == 1) {
                stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left+right);
        }
};

class Minus : public Command {
    public:
        void apply(std::stack<int> &stack) override {
            int size = stack.size();
            if (size == 0) throw interpreter_error("Stack underflow");
            if (size == 1) {
                stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left-right);
        }
};

class Multiply : public Command {
    public:
        void apply(std::stack<int> &stack) override {
            int size = stack.size();
            if (size == 0) throw interpreter_error("Stack underflow");
            if (size == 1) {
                stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left*right);
        }
};

class Dot : public Command {
    public:
        void apply(std::stack<int> &stack) override {
            if (stack.size() == 0) {
                throw interpreter_error("Stack underflow");
            }
            int top = stack.top();
            stack.pop();
            std::cout << top << std::endl;
        }
};