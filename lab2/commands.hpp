#pragma once
#include <iostream>
#include "context.hpp"
#include "interpreter_error.hpp"

class Command {
    public:
        typedef std::string::iterator str_iter;
        virtual void apply(context &context) = 0;
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
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left+right);
        }
};

class Minus : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left-right);
        }
};

class Multiply : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left*right);
        }
};

class Divide : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            if (right == 0) throw interpreter_error("Division by zero");
            stack.push(left/right);
        }
};

class Mod : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left % right);

        }
};

class Dot : public Command {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            if (stack.size() == 0) {
                throw interpreter_error("Stack underflow");
            }
            int top = stack.pop();
            context.out << top << ' ';
        }
};

class Less : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left < right);
        }
};

class More : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left > right);
        }
};

class Equal : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left == right);
        }
};

class Dup : public Command {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.push(stack.top());
        }
};

class Drop : public Command {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            stack.pop();
        }
};

class Swap : public BinaryOp {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int first = stack.pop();
            int second = stack.pop();
            stack.push(first);
            stack.push(second);
        }
};

class Emit : public Command {
    public: 
        void apply(context &context) override {
            datastack& stack = context.stack;
            if (stack.size() == 0) throw interpreter_error("Stack underflow");
            char c = stack.pop();
            context.out << c << std::endl;
        }
};

class Cr : public Command {
    public:
        void apply(context &context) override {
            context.out << std::endl;
        }
};

class Rot : public Command {
    public:
        void apply(context &context) override {
            datastack& stack = context.stack;
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
        void apply(context &context) override {
            datastack& stack = context.stack;
            checktwo(stack);
            int top = stack.pop();
            int back = stack.pop();
            stack.push(back);
            stack.push(top);
            stack.push(back);
        }
};

class Print : public Command {
    public:
        Print(std::string &str):body_(str){};
        void apply(context &context) override {
            context.out << body_ << std::endl;
        }
    private:
        std::string body_;
};
