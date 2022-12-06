#include "interpreter.hpp"

int main() {
    Interpreter &i = Interpreter::get_instance();
    std::string cmds;
    std::string output;
    while (true) {
        std::getline(std::cin, cmds);
        try {
            output = i.interpret(cmds.begin(), cmds.end());
            std::cout << output << std::endl;
        } catch (interpreter_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}