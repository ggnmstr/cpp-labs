#pragma once

#include <iostream>
#include <utility>
#include "context.hpp"
#include "interpreter_error.hpp"

class Command {
public:

    virtual void apply(context &context) = 0;

    virtual ~Command() = default;
};

class BinaryOperation : public Command {
public:
    void apply(context &context) override {
        int a = context.stack.pop();
        int b = context.stack.pop();
        context.stack.push(op()(b, a));
    }

    virtual std::function<int(int, int)> op() = 0;
};

class Push : public Command {
public:
    explicit Push(int n) : num_(n) {};

    void apply(context &context) override {
        context.stack.push(num_);
    }

private:
    int num_;
};

class Plus : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::plus<>();
    }
};

class Minus : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::minus<>();
    }
};

class Multiply : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::multiplies<>();
    }
};

class Divide : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return [](int lhs, int rhs) {
            if (rhs == 0) throw interpreter_error("Division by zero");
            return lhs / rhs;
        };
    }
};

class Mod : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return [](int lhs, int rhs) {
            if (rhs == 0) throw interpreter_error("Module by zero");
            return lhs % rhs;
        };
    }
};

class Dot : public Command {
public:
    void apply(context &context) override {
        datastack &stack = context.stack;
        int top = stack.pop();
        context.out << top << ' ';
    }
};

class Less : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::less<>();
    }
};

class More : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::greater<>();
    }
};

class Equal : public BinaryOperation {
public:
    std::function<int(int, int)> op() override {
        return std::equal_to<>();
    }
};

class Dup : public Command {
public:
    void apply(context &context) override {
        datastack &stack = context.stack;
        stack.push(stack.top());
    }
};

class Drop : public Command {
public:
    void apply(context &context) override {
        datastack &stack = context.stack;
        stack.pop();
    }
};

class Swap : public Command {
public:
    void apply(context &context) override {
        datastack &stack = context.stack;
        int first = stack.pop();
        int second = stack.pop();
        stack.push(first);
        stack.push(second);
    }
};

class Emit : public Command {
public:
    void apply(context &context) override {
        datastack &stack = context.stack;
        char c = stack.pop();
        context.out << c;
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
        datastack &stack = context.stack;
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
    void apply(context &context) override {
        datastack &stack = context.stack;
        int top = stack.pop();
        int back = stack.pop();
        stack.push(back);
        stack.push(top);
        stack.push(back);

    }
};

class Print : public Command {
public:
    explicit Print(std::string &str) : body_(str) {};

    void apply(context &context) override {
        context.out << body_ << ' ';
    }

private:
    std::string body_;
};

/*
class Ifbranch : public Command {
public:
    explicit Ifbranch(std::list<std::unique_ptr<Command>> thenlist) : thenbranch_(std::move(thenlist)) {};

    Ifbranch(std::list<std::unique_ptr<Command>> thenlist, std::list<std::unique_ptr<Command>> elselist)
            : thenbranch_(std::move(thenlist)), elsebranch_(std::move(elselist)) {};

    void apply(context &context) override {
        if (context.stack.top() == 0) return;
        if (elsebranch_.empty()){
            for (auto &x : thenbranch_){
                x->apply(context);
            }
        }
    }
private:
    std::list<std::unique_ptr<Command>> thenbranch_;
    std::list<std::unique_ptr<Command>> elsebranch_;
};
*/