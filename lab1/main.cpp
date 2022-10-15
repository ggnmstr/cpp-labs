#include "linkedhashset.hpp"
#include <iostream>
#include <vector>
#include <list>
int main(){
    student a1(19,"Jora");
    student a1c(19,"Jora");
    student a2(78,"Abrik");
    student a2c(78,"Abrik");
    student a3(22,"Anya");
    linkedhs l1; 
    linkedhs l2;
    // order of added elements effects opertor==, that's incorrect
    // should work on std::list<student> == std::list<student>
    l1.insert(a1);
    l1.insert(a2);
    l2.insert(a2c);
    l2.insert(a1c);
    std::cout << (l1 == l2) << std::endl;
    return 0;
}