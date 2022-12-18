#include <gtest/gtest.h>
#include "interpreter.hpp"

TEST(PlusTest, Simple) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd("200 300 + .");
    std::string x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "500 ");
}

TEST(PlusTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "+";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(PlusTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 +";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MinusTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "-";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MinusTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 -";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MultiplyTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "*";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MultiplyTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 *";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MultiplyTest, TwoNegatives) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "-1 -1 * .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "1 ");
}

TEST(ModuleTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "mod";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(ModuleTest, OneNumber) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "100 mod";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(ModuleTest, ByZero) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "100 0 mod";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DivideTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "/";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DivideTest, ByZero) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "100 0 /";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DivideTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 /";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DivideTest,Round){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "5 2 / .";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"2 ");
    cmd = "14 3 / .";
    x = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x,"4 ");
}

TEST(LessTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "<";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(LessTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 <";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(LessTest,Equal){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "42 42 < .";
    ASSERT_EQ(i.interpret(cmd.begin(), cmd.end()),"0 ");
}

TEST(MoreTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = ">";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MoreTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 >";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(MoreTest,Equal){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "42 42 > .";
    ASSERT_EQ(i.interpret(cmd.begin(), cmd.end()),"0 ");
}

TEST(EqualTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "=";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(EqualTest,Truth){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "42 42 = .";
    ASSERT_EQ(i.interpret(cmd.begin(), cmd.end()),"1 ");
}

TEST(EqualTest,Lie){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "12 34 = .";
    std::string x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "0 ");
}

TEST(DotTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = ".";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DupTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "dup";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DupTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 dup . .";
    std::string x  = i.interpret(cmd.begin(),cmd.end());
    ASSERT_EQ(x, "1 1 ");
}

TEST(DropTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "drop";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(DropTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 drop .";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(SwapTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "swap";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(SwapTest, TwoNums) {
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

TEST(EmitTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "emit";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(EmitTest,Output){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = " 33 119 111 87 emit emit emit emit";
    std::string x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x,"Wow!");
}

TEST(RotTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "rot";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(RotTest, OneNum) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd;
    cmd = "1 rot";
    ASSERT_THROW(i.interpret(cmd.begin(),cmd.end()),interpreter_error);
}

TEST(RotTest, TwoNums){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd;
    cmd = "1 2 rot";
    ASSERT_THROW(i.interpret(cmd.begin(),cmd.end()),interpreter_error);
}

TEST(RotTest, ThreeNums){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = "1 2 3 rot";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "ok");
    cmd = ". . .";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "1 3 2 ");
}

TEST(OverTest,Empty) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "over";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()), interpreter_error);
}

TEST(OverTest,OneNum){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd = "1 over";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(PrintTest,WrongCmd){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = ".\"";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}

TEST(PrintTest,Empty){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = ".\" ";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, " ");
}
TEST(PrintTest, ScreenSymbol) {
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = ".\" \\\"";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "\" ");
    cmd = ".\" \\\\";
    x = i.interpret(cmd.begin(), cmd.end());
    ASSERT_EQ(x, "\\ ");
}

TEST(PrintTest,WrongScreen){
    Interpreter &i = Interpreter::get_instance();
    std::string cmd, x;
    cmd = ".\" \\a";
    ASSERT_THROW(i.interpret(cmd.begin(), cmd.end()),interpreter_error);
}