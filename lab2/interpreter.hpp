#pragma once
#include <algorithm>
#include <iterator>
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>
#include "datastack.hpp"
#include "commands.hpp"

class Interpreter {
    public:
        typedef std::function<std::unique_ptr<Command> (std::string::iterator &, const std::string::iterator &)> creator_f;
        ~Interpreter() = default;

        static Interpreter & get_instance();

        bool register_creator(std::string symb, const creator_f &creator);

        // CR: void -> std::string
        std::string interpret(const std::string::iterator &begin, const std::string::iterator &end);

    private:

        std::unordered_map<std::string,creator_f> creators_;
        context context_;

        bool is_number(std::string &cmd);

        std::string get_symb(std::string::iterator &begin,const std::string::iterator &end);

        std::unique_ptr<Command>  get_cmd(std::string &symb, std::string::iterator &begin, const std::string::iterator &end);

        Interpreter() = default;

        Interpreter(Interpreter &other) = delete;
        Interpreter& operator=(Interpreter &other) = delete;
};