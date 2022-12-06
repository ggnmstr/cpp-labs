#pragma once
#include <iterator>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include "datastack.hpp"
#include "commands.hpp"

class Interpreter {
    public:
        typedef std::function<std::unique_ptr<Command> (std::string::iterator &, const std::string::iterator &)> creator_f;
        ~Interpreter() = default;

        static Interpreter & get_instance();

        bool register_creator(const creator_f &creator);

        std::string interpret(const std::string::iterator &begin, const std::string::iterator &end);

    private:

        // CR: unordered_map -> vector
        std::vector<creator_f> creators_;
        datastack stack_;

        Interpreter() = default;

        Interpreter(Interpreter &other) = delete;
        Interpreter& operator=(Interpreter &other) = delete;
};