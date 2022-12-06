#pragma once
#include <stack>

class datastack{
    public:
        int pop();
        int top();
        void push(int x);

    private:
        std::stack<int> stack_;
};