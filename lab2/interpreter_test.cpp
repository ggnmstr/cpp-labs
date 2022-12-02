#include <gtest/gtest.h>
#include "interpreter.hpp"

TEST(PlusTest,Simple){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd("200 300 + .");
    std::string x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x , "500 ");
}