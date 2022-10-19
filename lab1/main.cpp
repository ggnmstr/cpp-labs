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
    student a3c(22,"Anya");
    student a4(20,"Misha");
    student a5(22, "Katya");
    student a6(16,"Gennady");
    linkedhs lhs1;
    lhs1.insert(a1);
    lhs1.insert(a2);
    lhs1.insert(a3);
    lhs1.insert(a4);
    lhs1.insert(a5);
    lhs1.insert(a6);
    linkedhs::iterator it = lhs1.find(a3);
    std::cout << a3.hash() << std::endl;
    std::cout << (*it).hash() << std::endl;
    it++;
    std::cout << a4.hash() << std::endl;
    std::cout << (*it).hash() << std::endl;
    --it;
    std::cout << a3.hash() << std::endl;
    std::cout << (*it).hash() << std::endl;
    return 0;
}