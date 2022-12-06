#include "interpreter.hpp"
#include <algorithm>
#include <cassert>

Interpreter &Interpreter::get_instance() {
    static Interpreter i;
    return i;
}

bool Interpreter::register_creator(const creator_f &creator) {
    creators_.push_back(creator);
    return true;
}

std::string Interpreter::interpret(const std::string::iterator &begin, const std::string::iterator &end) {
    context context(stack_);
    std::string::iterator itbeg = begin;
    while (itbeg != end) {
        // move itbeg to first non-blank symbol
        itbeg = std::find_if_not(itbeg, end, ::isblank);
        if (itbeg == end) break;
        std::unique_ptr<Command> cmd;
        for (const creator_f &creator: creators_) {
            cmd = creator(itbeg, end);
            if (cmd != nullptr) break;
        }
        if (cmd == nullptr) throw interpreter_error("unknown cmd");
        try {
            cmd->apply(context);
        } catch (interpreter_error &e) {
            context.out << e.what();
        }
    }
    std::string str = context.out.str();
    return str.empty() ? "ok" : str;
}