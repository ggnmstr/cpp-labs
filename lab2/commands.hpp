#pragma once
#include <stack>
#include <iostream>
#include "interpreter_error.hpp"

class Command {
    public:
        typedef std::string::iterator striter;
        virtual void apply(std::stack<int> &stack, striter &begin, const striter &end) = 0;
        virtual ~Command() {}
        void checktwo(std::stack<int> &stack){
            int size = stack.size();
            if (size == 0) throw interpreter_error("Stack underflow");
            if (size == 1) {
                stack.pop();
                throw interpreter_error("Stack underflow");
            }
        }
};

class Plus : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left+right);
        }
};

class Minus : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left-right);
        }
};

class Multiply : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left*right);
        }
};

class Divide : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            if (right == 0) throw interpreter_error("Division by zero");
            stack.push(left/right);
        }
};

class Mod : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left % right);

        }
};

class Dot : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            if (stack.size() == 0) {
                throw interpreter_error("Stack underflow");
            }
            int top = stack.top();
            stack.pop();
            //std::cout << top << std::endl;
            std::cout << top << ' ';
        }
};

class Less : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left < right);
        }
};

class More : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left > right);
        }
};

class Equal : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            stack.push(left == right);
        }
};

class Dup : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.push(stack.top());
        }
};

class Drop : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.pop();
        }
};

class Swap : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int first = stack.top();
            stack.pop();
            int second = stack.top();
            stack.pop();
            stack.push(first);
            stack.push(second);
        }
};

class Emit : public Command {
    public: 
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            char c = stack.top();
            stack.pop();
            std::cout << c << std::endl;
        }
};

class Cr : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            std::cout << std::endl;
        }
};

class Rot : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            int size = stack.size(); 
            if (size < 3) {
                for (int i = 0; i < size; i++) stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int three = stack.top();
            stack.pop();
            int two = stack.top();
            stack.pop();
            int one = stack.top();
            stack.pop();
            stack.push(two);
            stack.push(three);
            stack.push(one);
        }
};

class Over : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            checktwo(stack);
            int top = stack.top();
            stack.pop();
            int back = stack.top();
            stack.pop();
            stack.push(back);
            stack.push(top);
            stack.push(back);
        }
};

class Print : public Command {
    public:
        void apply(std::stack<int> &stack, striter &begin, const striter &end) override {
            
            //std::cout << "PRINt!!" << std::endl;
            begin++;
            while (begin != end && *begin != '"') {
                std::cout << *begin;
                begin++;
            }
            if (*begin == '"') begin++;
            std::cout << std::endl;
        }
};