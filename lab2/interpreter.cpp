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

std::list<std::unique_ptr<Command>> Interpreter::get_cmds(const std::string::iterator &begin, const std::string::iterator &end) {
    std::list<std::unique_ptr<Command>> cmdlist;
    std::string::iterator itbeg = begin;
    while(itbeg != end){
        itbeg = std::find_if_not(itbeg, end, ::isblank);
        if (itbeg == end) break;
        std::unique_ptr<Command> cmd;
        //std::cout << "TRYING TO INTERPRET PART:\"" << std::string(itbeg,end) << "\"" << std::endl;
        for (const creator_f &creator: creators_) {
            cmd = creator(itbeg, end);
            if (cmd != nullptr) break;
        }
        if (cmd == nullptr) throw interpreter_error("Unknown cmd");
        cmdlist.push_back(std::move(cmd));
    }
    return cmdlist;
}

std::string Interpreter::interpret(const std::string::iterator &begin, const std::string::iterator &end) {
    context context(stack_);
    const std::list<std::unique_ptr<Command>> &cmdlist = get_cmds(begin,end);
    try {
        for (const std::unique_ptr<Command> &cmdptr : cmdlist){
            Command *cmd = cmdptr.get();
            cmd->apply(context);
        }
    } catch (interpreter_error &e){
        context.out << e.what();
    }
    if (context.out.str().empty()) context.out << "ok";
    return context.out.str();
}