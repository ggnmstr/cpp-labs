#include <stack>
#include "interpreter.hpp"
#include "commands.hpp"

namespace { 
    bool plus = Interpreter::get_instance().register_cmd("+", new Plus());
    bool minus = Interpreter::get_instance().register_cmd("-",new Minus());
    bool multiply = Interpreter::get_instance().register_cmd("*",new Multiply());
    bool divide = Interpreter::get_instance().register_cmd("/", new Divide());
    bool mod = Interpreter::get_instance().register_cmd("mod",new Mod());

    bool less = Interpreter::get_instance().register_cmd("<",new Less());
    bool more = Interpreter::get_instance().register_cmd(">",new More());
    bool equal = Interpreter::get_instance().register_cmd("=",new Equal());

    bool dot = Interpreter::get_instance().register_cmd(".", new Dot());

    bool dup = Interpreter::get_instance().register_cmd("dup",new Dup());
    bool drop = Interpreter::get_instance().register_cmd("drop",new Drop());
    bool swap = Interpreter::get_instance().register_cmd("swap",new Swap());
    bool emit = Interpreter::get_instance().register_cmd("emit",new Emit());
    bool cr = Interpreter::get_instance().register_cmd("cr",new Cr());
    bool rot = Interpreter::get_instance().register_cmd("rot",new Rot());
    bool over = Interpreter::get_instance().register_cmd("over",new Over());


}