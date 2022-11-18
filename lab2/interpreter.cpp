#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <stack>
#include <vector>

bool is_number(std::string &cmd){
    for (auto x : cmd){
        if (!isdigit(x)) return false;
    }
    return true;
}

class Interpreter {
    public:
        static Interpreter & get_instance(){
            static Interpreter i;
            return i;
        }

        //void interpret(std::string::iterator &begin, std::string::iterator &end){
        void interpret(std::string &cmds){
            
            std::istringstream iss(cmds);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>{}};

            for (std::string & cmd : tokens){
                if (is_number(cmd)){
                    std::cout << "PUSHED TO STACK:";
                    stack_.push(std::stoi(cmd));
                };
                std::cout << cmd << std::endl;
            }
        }

    private:
        Interpreter() = default;

        Interpreter(Interpreter &other) = delete;
        Interpreter& operator=(Interpreter &other) = delete;

        std::stack<int> stack_;

};