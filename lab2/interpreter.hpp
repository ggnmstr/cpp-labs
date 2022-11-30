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
        //typedef std::function<Command *(std::vector<std::string>::iterator &,std::vector<std::string>::iterator &)> creator_f;
        ~Interpreter();

        static Interpreter & get_instance();

        bool register_cmd(std::string symb, Command *cmd);

        // CR: void -> std::string
        void interpret(const std::string::iterator &begin, const std::string::iterator &end);

    private:

        // CR: Command * -> unique_ptr<Command>
        std::unordered_map<std::string,Command*> cmds_;
        std::stack<int> stack_;

        bool is_number(std::string &cmd);

        std::string get_symb(std::string::iterator &begin,const std::string::iterator &end);

        Command *get_cmd(std::string &symb);

        Interpreter() = default;

        Interpreter(Interpreter &other) = delete;
        Interpreter& operator=(Interpreter &other) = delete;
};