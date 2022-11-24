#include <iostream>
#include "interpreter.hpp"

int main(){
    Interpreter &i = Interpreter::get_instance();
    std::string cmds;
    while (true)
    {
        std::cin >> cmds;
        i.interpret(cmds);
    }
    return 0;
}