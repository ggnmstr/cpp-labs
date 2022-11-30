#pragma once
#include <stack>
#include <iostream>
#include "interpreter_error.hpp"

class Command {
    public:
        typedef std::string::iterator str_iter;
        virtual void apply(datastack &stack, str_iter &begin, const str_iter &end) = 0;
        virtual ~Command() {}
        // CR: class BinaryOp: Command
        void checktwo(datastack &stack){
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
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left+right);
        }
};

class Minus : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left-right);
        }
};

// CR:
//class data_stack {
//public:
//    int pop() {
//
//    }
//private:
//    std::stack<int> stack_;
//};

class Multiply : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left*right);
        }
};

class Divide : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            if (right == 0) throw interpreter_error("Division by zero");
            stack.push(left/right);
        }
};

class Mod : public Command {
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

class Less : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left < right);
        }
};

class More : public Command {
    public:
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            checktwo(stack);
            int right = stack.pop();
            int left = stack.pop();
            stack.push(left > right);
        }
};

class Equal : public Command {
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

class Swap : public Command {
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

class Over : public Command {
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
        void apply(datastack &stack, str_iter &begin, const str_iter &end) override {
            
            //std::cout << "PRINt!!" << std::endl;
            // CR: escape ." \"" , ." \\"
            if (begin != end) begin++;
            while (begin != end && *begin != '"') {
                std::cout << *begin;
                begin++;
            }
            if (*begin == '"') begin++;
            std::cout << std::endl;
        }
};
