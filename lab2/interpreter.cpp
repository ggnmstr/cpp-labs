#include "interpreter.hpp"

Interpreter & Interpreter::get_instance(){
            static Interpreter i;
            return i;
}

Interpreter::~Interpreter(){  
    for (auto e : cmds_){
        delete e.second;
    }
}

bool Interpreter::register_cmd(std::string symb, Command *cmd){
    cmds_[symb] = cmd;
    return true;
}

void Interpreter::interpret(const std::string::iterator &begin, const std::string::iterator &end){
    std::string::iterator itbeg = begin;
    while (itbeg != end){
        // ." foo bar "
        std::string symb = get_symb(itbeg,end);
        if (symb == "") continue;
        //std::cout <<"'" << symb << "'" << std::endl;
        if (is_number(symb)){
            stack_.push(std::stoi(symb));
            continue;
        }
        try {
            Command *cmd = get_cmd(symb);
            // ss -> empty -> ok
            // ss -> not empty -> ss
            cmd->apply(stack_,itbeg,end);
        } catch (interpreter_error &e){
            std::cerr << e.what() << std::endl;
        }
    }
}

bool Interpreter::is_number(std::string &cmd){
    std::string::iterator beg = cmd.begin();
    if (cmd[0] == '-') beg++;
    // CR: find_if
    for (;beg != cmd.end(); beg++){
        if (!isdigit(*beg)) return false;
    }
    return true;
}

std::string Interpreter::get_symb(std::string::iterator &begin,const std::string::iterator &end){
    //while (begin != end && (*begin == ' ' || *begin == '\t')) begin++;
    // CR: find_if
    while (begin != end && *begin == ' ') begin++;
    std::string::iterator itend = begin;
    //while (itend != end && (*itend != ' ' || *itend != '\t')) itend++;
    while (itend != end && *itend != ' ') itend++;
    std::string x(begin,itend);
    begin = itend;
    return x;   
}

Command* Interpreter::get_cmd(std::string &symb){
    auto cmd_it = cmds_.find(symb);

    if (cmd_it == cmds_.end()) {
        std::stringstream ss; 
        ss << "Command " << "'" << symb << "'" << " not found";
        throw interpreter_error(ss.str());
    }
    Command *cmd = (*cmd_it).second;
    return cmd;
}