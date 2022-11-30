#pragma once
#include <stack>

class datastack{
    public:
        int pop();
        int top();
        void push(int x);
        int size();

    private:
        std::stack<int> stack_;
};