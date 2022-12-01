#pragma once
#include <stack>
#include <iostream>
#include "interpreter_error.hpp"

class Command {
    public:
        typedef std::string::iterator str_iter;
        virtual void apply(datastack &stack, str_iter &begin, const str_iter &end) = 0;
        virtual ~Command() {}
};

class BinaryOp : public Command {
    public:
        void checktwo(datastack &stack){
        int size = stack.size();
        if (size == 0) throw interpreter_error("Stack underflow");
        if (size == 1) {
            stack.pop();
            throw interpreter_error("Stack underflow");
            }
        }
};

class Plus : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left+right);
        }
};

class Minus : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left-right);
        }
};

class Multiply : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left*right);
        }
};

class Divide : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            if (right == 0) throw interpreter_error("Division by zero");
            stack.push(left/right);
        }
};

class Mod : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left % right);

        }
};

class Dot : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            if (stack.size() == 0) {
                throw interpreter_error("Stack underflow");
            }
            int top = stack.pop();
            //std::cout << top << std::endl;
            std::cout << top << ' ';
        }
};

class Less : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left < right);
        }
};

class More : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left > right);
        }
};

class Equal : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left == right);
        }
};

class Dup : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.push(stack.top());
        }
};

class Drop : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.pop();
        }
};

class Swap : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int first = stack.pop();
            int second = stack.pop();
            stack.push(first);
            stack.push(second);
        }
};

class Emit : public Command {
    public: 
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            char c = stack.pop();
            std::cout << c << std::endl;
        }
};

class Cr : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            std::cout << std::endl;
        }
};

class Rot : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            int size = stack.size(); 
            if (size < 3) {
                for (int i = 0; i < size; i++) stack.pop();
                throw interpreter_error("Stack underflow");
            }
            int three = stack.pop();
            int two = stack.pop();
            int one = stack.pop();
            stack.push(two);
            stack.push(three);
            stack.push(one);
        }
};

class Over : public BinaryOp {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int top = stack.pop();
            int back = stack.pop();
            stack.push(back);
            stack.push(top);
            stack.push(back);
        }
};

// CR: pass to apply
//struct context {
//    data_stack &stack;
//    str_iter &begin;
//    std::stringstream out;
//    const str_iter &en;
//};

class Print : public Command {
    public:
        Print(std::string &str):body_(str){};
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            std::cout << body_ << std:: endl;
            // CR: escape ." \"" , ." \\"
        }
    private:
        std::string body_;
};
