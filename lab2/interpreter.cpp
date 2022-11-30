#include "interpreter.hpp"

Interpreter & Interpreter::get_instance(){
            static Interpreter i;
            return i;
}

//Interpreter::~Interpreter(){
//    for (auto e : creators_){
//        delete e.second;
//    }
//}

bool Interpreter::register_creator(std::string symb, const creator_f &creator){
    creators_[symb] = creator;
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
            std::unique_ptr<Command> cmd = get_cmd(symb);
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

std::unique_ptr<Command> Interpreter::get_cmd(std::string &symb){
    auto cmd_it = creators_.find(symb);

    if (cmd_it == creators_.end()) {
        std::stringstream ss; 
        ss << "Command " << "'" << symb << "'" << " not found";
        throw interpreter_error(ss.str());
    }
    creator_f creator = (*cmd_it).second;
    std::unique_ptr<Command> cmd = creator(symb);
    return cmd;
}