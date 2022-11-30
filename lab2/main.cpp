#include "interpreter.hpp"

int main(){
    Interpreter &i = Interpreter::get_instance();
    std::string cmds;
    while (true)
    {
        std::getline(std::cin,cmds);
        //std::cout << "Getlined!" << std::endl;
        //i.interpret(cmds);
        i.interpret(cmds.begin(),cmds.end());
    }
    return 0;
}