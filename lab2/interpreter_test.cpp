#include <gtest/gtest.h>
#include "interpreter.hpp"

TEST(PlusTest,Simple){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd("200 300 + .");
    std::string x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x , "500 ");
}

TEST(EmptyTest,Everything){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "+";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");
    
    cmd = "-";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "*";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "mod";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "/";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "<";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = ">";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "=";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = ".";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");
    
    cmd = "dup";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "drop";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "swap";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "emit";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "rot";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");

    cmd = "over";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Stack underflow");
}

TEST(MultiplyTest,TwoNegatives){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "-1 -1 * .";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"1 ");
}

TEST(DivideTest,DivisionByZero){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "100 0 /";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Division by zero");
}

TEST(ModuleTest,ModuleByZero){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "100 0 mod";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"Module by zero");
}