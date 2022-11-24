#include <stack>
#include "interpreter.hpp"
#include "commands.hpp"

namespace { 
    bool plus = Interpreter::get_instance().register_cmd("+", new Plus());
    bool minus = Interpreter::get_instance().register_cmd("-",new Minus());
    bool multiply = Interpreter::get_instance().register_cmd("*",new Multiply());
    bool dot = Interpreter::get_instance().register_cmd(".", new Dot());

}