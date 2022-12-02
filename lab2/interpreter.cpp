#include "interpreter.hpp"
#include <cassert>
Interpreter & Interpreter::get_instance(){
            static Interpreter i;
            return i;
}

bool Interpreter::register_creator(std::string symb, const creator_f &creator){
    creators_[symb] = creator;
    return true;
}

std::string Interpreter::interpret(const std::string::iterator &begin, const std::string::iterator &end){
    // CR: make context local variable
    context_.out.str(std::string());
    std::string::iterator itbeg = begin;
    while (itbeg != end){
        std::string prefix = get_prefix(itbeg, end);
        if (prefix.empty()) continue;
        if (is_number(prefix)){
            // CR: make command Push
            context_.stack.push(std::stoi(prefix));
            continue;
        }
        try {
            std::unique_ptr<Command> cmd = get_cmd(prefix, itbeg, end);
            cmd->apply(context_);
        } catch (interpreter_error &e){
            context_.out << e.what();
        }
    }
    std::string str = context_.out.str();
    return str.empty() ? "ok" : str;
}

bool Interpreter::is_number(std::string &cmd){
    assert(!cmd.empty());
    std::string::iterator beg = cmd.begin();
    if (cmd[0] == '-') {
        if (cmd.length() == 1) return false;
        beg++;
    }
    auto non_digit_it = std::find_if_not(beg, cmd.end(), ::isdigit);
    return non_digit_it == cmd.end();
}

std::string Interpreter::get_prefix(std::string::iterator &begin, const std::string::iterator &end){
    // CR: https://en.cppreference.com/w/cpp/string/byte/isblank
    begin = std::find_if(begin,end,[](char x){return x != ' ';});
    std::string::iterator itend = begin;

    itend = std::find_if(itend, end,[](char x){return x == ' ';});

    std::string x(begin,itend);
    begin = itend;
    return x;   
}

std::unique_ptr<Command> Interpreter::get_cmd(std::string &symb, std::string::iterator &begin, const std::string::iterator &end){
    auto cmd_it = creators_.find(symb);

    if (cmd_it == creators_.end()) {
        std::stringstream ss; 
        ss << "Command " << "'" << symb << "'" << " not found";
        throw interpreter_error(ss.str());
    }
    creator_f creator = (*cmd_it).second;
    std::unique_ptr<Command> cmd = creator(begin,end);
    return cmd;
}