#include <stack>
#include "interpreter.hpp"
#include "commands.hpp"

namespace { 
    bool plus = Interpreter::get_instance().register_cmd("+", new Plus());
    bool dot = Interpreter::get_instance().register_cmd(".", new Dot());

}