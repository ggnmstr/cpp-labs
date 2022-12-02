#include <memory>
#include "interpreter.hpp"
#include "commands.hpp"

namespace {

    // arithmetic operations //
    std::unique_ptr<Command> plus_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Plus>();
        return ptr;
    } 
    bool plus = Interpreter::get_instance().register_creator("+", plus_creator);

    std::unique_ptr<Command> minus_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Minus>();
        return ptr;
    }
    bool minus = Interpreter::get_instance().register_creator("-",minus_creator);

    std::unique_ptr<Command> multiply_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Multiply>();
        return ptr;
    }
    bool multiply = Interpreter::get_instance().register_creator("*",multiply_creator);

    std::unique_ptr<Command> divide_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Divide>();
        return ptr;
    }
    bool divide = Interpreter::get_instance().register_creator("/", divide_creator);

    std::unique_ptr<Command> mod_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Mod>();
        return ptr;
    }
    bool mod = Interpreter::get_instance().register_creator("mod",mod_creator);

    // logic operations //

    std::unique_ptr<Command> less_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Less>();
        return ptr;
    }
    bool less = Interpreter::get_instance().register_creator("<",less_creator);

    std::unique_ptr<Command> more_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<More>();
        return ptr;
    }
    bool more = Interpreter::get_instance().register_creator(">",more_creator);

    std::unique_ptr<Command> equal_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Equal>();
        return ptr;
    }
    bool equal = Interpreter::get_instance().register_creator("=",equal_creator);

    // print functions //

    std::unique_ptr<Command> dot_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Dot>();
        return ptr;
    }
    bool dot = Interpreter::get_instance().register_creator(".", dot_creator);

    std::unique_ptr<Command> print_creator(std::string::iterator &begin, const std::string::iterator &end){
        std::string str;
        // CR: *end() is ub
        // CR: short path
        if (begin != end) begin++;
        for (;begin != end; begin++){
            if (*begin == '\\') {
                // CR: escape for " and backslash only
                begin++;
                str+= *begin;
                continue;
            }
            if (*begin == '"') break;
            str+= *begin;
        }
        // CR: *end() is ub
        if (*begin == '"') begin++;
        return std::make_unique<Print>(str);
    }
    bool print = Interpreter::get_instance().register_creator(".\"",print_creator);


    // stack manipulations //

    std::unique_ptr<Command> dup_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Dup>();
        return ptr;
    }
    bool dup = Interpreter::get_instance().register_creator("dup",dup_creator);

    std::unique_ptr<Command> drop_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Drop>();
        return ptr;
    }
    bool drop = Interpreter::get_instance().register_creator("drop",drop_creator);

    std::unique_ptr<Command> swap_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Swap>();
        return ptr;
    }
    bool swap = Interpreter::get_instance().register_creator("swap",swap_creator);

    std::unique_ptr<Command> emit_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Emit>();
        return ptr;
    }
    bool emit = Interpreter::get_instance().register_creator("emit",emit_creator);

    std::unique_ptr<Command> cr_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Cr>();
        return ptr;
    }
    bool cr = Interpreter::get_instance().register_creator("cr",cr_creator);

    std::unique_ptr<Command> rot_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Rot>();
        return ptr;
    }
    bool rot = Interpreter::get_instance().register_creator("rot",rot_creator);

    std::unique_ptr<Command> over_creator(std::string::iterator &begin, const std::string::iterator &end){
        auto ptr = std::make_unique<Over>();
        return ptr;
    }
    bool over = Interpreter::get_instance().register_creator("over",over_creator);


}