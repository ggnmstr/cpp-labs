#include <gtest/gtest.h>
#include "interpreter.hpp"

TEST(PlusTest, Simple) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd("200 300 + .");
    std::string x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "500 ");
}

TEST(EmptyTest, Everything) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "+";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "-";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "*";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "mod";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "/";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "<";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = ">";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "=";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = ".";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "dup";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "drop";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "swap";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "emit";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "rot";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");

    cmd = "over";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");
}

TEST(MultiplyTest, TwoNegatives) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "-1 -1 * .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "1 ");
}
// CR: ByZero, Empty, OneNumber, Round, IntegerDivision
TEST(DivideTest, DivisionByZero) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "100 0 /";
    x = i.interpret(cmd.begin(), cmd.end());
    // CR: check that exception is thrown
    ASSERT_EQ(x, "Division by zero");
}

TEST(ModuleTest, ModuleByZero) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "100 0 mod";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Module by zero");
}

TEST(SwapTest, SwapTwoThree) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "1 2 swap";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "ok");
    cmd = ". .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "1 2 ");
    cmd = "1 2 swap swap . .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "2 1 ");

}

TEST(PrintTest, SpecificSymbols) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = ".\" \\\"";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "\" ");
    cmd = ".\" \\\\";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "\\ ");
}

TEST(RotTest, RotTest) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "1 rot";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");
    cmd = "1 2 rot";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "Stack underflow");
    cmd = "1 2 3 rot";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "ok");
    cmd = ". . .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "1 3 2 ");
}