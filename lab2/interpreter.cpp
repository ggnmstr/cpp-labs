#include "interpreter.hpp"

Interpreter & Interpreter::get_instance(){
            static Interpreter i;
            return i;
}

bool Interpreter::register_creator(std::string symb, const creator_f &creator){
    creators_[symb] = creator;
    return true;
}

std::string Interpreter::interpret(const std::string::iterator &begin, const std::string::iterator &end){
    context_.out.str(std::string());
    std::string::iterator itbeg = begin;
    while (itbeg != end){
        std::string symb = get_symb(itbeg,end);
        if (symb == "") continue;
        if (is_number(symb)){
            context_.stack.push(std::stoi(symb));
            continue;
        }
        try {
            std::unique_ptr<Command> cmd = get_cmd(symb,itbeg,end);
            cmd->apply(context_);
        } catch (interpreter_error &e){
            context_.out << e.what();
        }
    }
    std::string str = context_.out.str();
    return str.empty() ? "ok" : str;
}

bool Interpreter::is_number(std::string &cmd){
    std::string::iterator beg = cmd.begin();
    if (cmd[0] == '-' && cmd.length() != 1) beg++;

    auto it = std::find_if(beg,cmd.end(),[](char x){return !isdigit(x);});
    if (it != cmd.end()) return false;
    return true;
}

std::string Interpreter::get_symb(std::string::iterator &begin,const std::string::iterator &end){
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