#include <memory>
#include <algorithm>
#include "interpreter.hpp"
#include "commands.hpp"

bool is_valid(std::string::iterator &begin, const std::string::iterator &end, const std::string &str) {
    std::string::iterator bcopy = std::find_if(begin, end, ::isblank);
    if (std::equal(begin, bcopy, str.begin(), str.end())) {
        begin = bcopy;
        return true;
    }
    return false;
}

namespace {

    std::unique_ptr<Command> push_creator(std::string::iterator &begin, const std::string::iterator &end) {
        std::string::iterator bcopy = begin;
        if (bcopy != end && *bcopy == '-') ++bcopy;
        if (bcopy == end || std::isblank(*bcopy) || !std::isdigit(*bcopy)) return std::unique_ptr<Command>(nullptr);
        auto ncheck = std::find_if_not(bcopy, end, ::isdigit);
        if (::isblank(*ncheck) || ncheck == end) {
            auto ptr = std::make_unique<Push>(std::stoi(std::string(begin, ncheck)));
            begin = ncheck;
            return ptr;
        }
        return std::unique_ptr<Command>(nullptr);
    }

    bool push = Interpreter::get_instance().register_creator(push_creator);

    // arithmetic operations //
    std::unique_ptr<Command> plus_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "+")) return std::make_unique<Plus>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool plus = Interpreter::get_instance().register_creator(plus_creator);

    std::unique_ptr<Command> minus_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "-")) return std::make_unique<Minus>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool minus = Interpreter::get_instance().register_creator(minus_creator);

    std::unique_ptr<Command> multiply_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "*")) return std::make_unique<Multiply>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool multiply = Interpreter::get_instance().register_creator(multiply_creator);

    std::unique_ptr<Command> divide_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "/")) return std::make_unique<Divide>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool divide = Interpreter::get_instance().register_creator(divide_creator);

    std::unique_ptr<Command> mod_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "mod")) return std::make_unique<Mod>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool mod = Interpreter::get_instance().register_creator(mod_creator);

    // logic operations //

    std::unique_ptr<Command> less_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "<")) return std::make_unique<Less>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool less = Interpreter::get_instance().register_creator(less_creator);

    std::unique_ptr<Command> more_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, ">")) return std::make_unique<More>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool more = Interpreter::get_instance().register_creator(more_creator);

    std::unique_ptr<Command> equal_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "=")) return std::make_unique<Equal>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool equal = Interpreter::get_instance().register_creator(equal_creator);

    // print functions //

    std::unique_ptr<Command> dot_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, ".")) return std::make_unique<Dot>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool dot = Interpreter::get_instance().register_creator(dot_creator);

    std::unique_ptr<Command> print_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (!is_valid(begin, end, ".\"")) return std::unique_ptr<Command>(nullptr);
        if (begin == end) return std::unique_ptr<Command>(nullptr);
        std::string str;
        ++begin;
        for (; begin != end; ++begin) {
            if (*begin == '\\') {
                ++begin;
                if (*begin != '\"' && *begin != '\\' ) throw interpreter_error("Wrong escape character");
                str += *begin;
                continue;
            }
            if (*begin == '"') break;
            str += *begin;
        }
        if (begin != end && *begin == '"') ++begin;
        return std::make_unique<Print>(str);
    }

    bool print = Interpreter::get_instance().register_creator(print_creator);


    // stack manipulations //

    std::unique_ptr<Command> dup_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "dup")) return std::make_unique<Dup>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool dup = Interpreter::get_instance().register_creator(dup_creator);

    std::unique_ptr<Command> drop_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "drop")) return std::make_unique<Drop>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool drop = Interpreter::get_instance().register_creator(drop_creator);

    std::unique_ptr<Command> swap_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "swap")) return std::make_unique<Swap>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool swap = Interpreter::get_instance().register_creator(swap_creator);

    std::unique_ptr<Command> emit_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "emit")) return std::make_unique<Emit>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool emit = Interpreter::get_instance().register_creator(emit_creator);

    std::unique_ptr<Command> cr_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "cr")) return std::make_unique<Cr>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool cr = Interpreter::get_instance().register_creator(cr_creator);

    std::unique_ptr<Command> rot_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "rot")) return std::make_unique<Rot>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool rot = Interpreter::get_instance().register_creator(rot_creator);

    std::unique_ptr<Command> over_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (is_valid(begin, end, "over")) return std::make_unique<Over>();
        return std::unique_ptr<Command>(nullptr);
    }

    bool over = Interpreter::get_instance().register_creator(over_creator);

/*
    // ADVANCED VERSION:
    // -----------------------

    std::unique_ptr<Command> if_creator(std::string::iterator &begin, const std::string::iterator &end) {
        if (!is_valid(begin,end,"if")) return std::unique_ptr<Command>(nullptr);
        std::string::iterator semicolon_it = std::find_if(begin,end,[](char x){return x == ';';});
        if (semicolon_it == end) throw interpreter_error("No semicolon at the end of if statement");
        std::string strcopy(begin,end);
        std::string::iterator begcopy = begin;
//        std::cout << "CURBEGIN = " << *begin << std::endl;
        size_t elseex = strcopy.find(" else ");
        if (elseex == std::string::npos){
            size_t then = strcopy.find(" then ");
            if (then == std::string::npos) throw interpreter_error("Invalid syntax (no then)");
            begcopy += then;
//            std::cout << "THEN = " << then << std::endl;
//            std::cout << "INTERPRETING:\"" << std::string(begin,begcopy) << "\"" << std::endl;
            std::list<std::unique_ptr<Command>> thenbranch = Interpreter::get_instance().get_cmds(begin,begcopy);
            begin = ++semicolon_it;
            return std::make_unique<Ifbranch>(std::move(thenbranch));
        }




    }

    bool ifbranch = Interpreter::get_instance().register_creator(if_creator);
*/

}