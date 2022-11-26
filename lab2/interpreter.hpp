#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stack>
#include <functional>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "commands.hpp"

class Interpreter {
    public:
        typedef std::function<Command *(std::vector<std::string>::iterator &,std::vector<std::string>::iterator &)> creator_f;
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

        std::string get_symb(std::string::iterator &begin,const std::string::iterator &end){
            //while (begin != end && (*begin == ' ' || *begin == '\t')) begin++;
            while (begin != end && *begin == ' ') begin++;
            std::string::iterator itend = begin;
            //while (itend != end && (*itend != ' ' || *itend != '\t')) itend++;
            while (itend != end && *itend != ' ') itend++;
            std::string x(begin,itend);
            begin = itend;
            return x;
            
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

        //void interpret(const std::string &cmds){
        void interpret(const std::string::iterator &begin, const std::string::iterator &end){
            std::string::iterator itbeg = begin;
            // std::istringstream iss(cmds);
            // std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
            //         std::istream_iterator<std::string>{}};
            while (itbeg != end){
                std::string symb = get_symb(itbeg,end);
                if (symb == "") continue;
                //std::cout <<"'" << symb << "'" << std::endl;
                if (is_number(symb)){
                    stack_.push(std::stoi(symb));
                    continue;
                }
                try {
                    Command *cmd = get_cmd(symb);
                    cmd->apply(stack_);
                } catch (interpreter_error &e){
                    std::cerr << e.what() << std::endl;
                }
            }

            /*
            //for (std::string & symb : tokens){
            for (auto it = tokens.begin(); it != tokens.end(); it++){
                std::string & symb = (*it);
                if (is_number(symb)){
                    //std::cout << "PUSHED TO STACK:" << symb << std::endl;
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
            */
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