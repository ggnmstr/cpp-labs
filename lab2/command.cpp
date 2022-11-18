#include <stack>

class Command {
    public:
        virtual void apply(std::stack<int> &stack) = 0;
        virtual ~Command() {}

};