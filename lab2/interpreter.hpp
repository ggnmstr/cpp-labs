#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "commands.hpp"

class Interpreter {
    public:

        ~Interpreter(){
            for (auto e : cmds_){
                delete e.second;
            }
        }

        static Interpreter & get_instance(){
            static Interpreter i;
            return i;
        }

        bool register_cmd(std::string symb, Command *cmd){
            cmds_[symb] = cmd;
            return true;
        }

        Command *get_cmd(std::string &symb){
            auto cmd_it = cmds_.find(symb);

            if (cmd_it == cmds_.end()) {
                std::stringstream ss; 
                ss << "Command " << symb << " not found";
                throw interpreter_error(ss.str());
            }
            Command *cmd = (*cmd_it).second;
            return cmd;
        }

        //void interpret(std::string::iterator &begin, std::string::iterator &end){
        void interpret(std::string &cmds){
            
            std::istringstream iss(cmds);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>{}};

            for (std::string & symb : tokens){
                if (is_number(symb)){
                    std::cout << "PUSHED TO STACK:" << symb << std::endl;
                    stack_.push(std::stoi(symb));
                    continue;
                };
                try{
                    Command *cmd = get_cmd(symb);
                    //std::cout << cmd << std::endl;
                    cmd->apply(stack_);
                } catch (interpreter_error &e) {
                    std::cerr << e.what() << std::endl;
                }
                
            }
        }

    private:

        bool is_number(std::string &cmd){
            for (auto x : cmd){
                if (!isdigit(x)) return false;
            }
            return true;
        }

        Interpreter() = default;

        Interpreter(Interpreter &other) = delete;
        Interpreter& operator=(Interpreter &other) = delete;

        std::unordered_map<std::string,Command*> cmds_;
        std::stack<int> stack_;

};