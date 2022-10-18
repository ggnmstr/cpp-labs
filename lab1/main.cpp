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
    linkedhs l1;
    linkedhs l2;

    l1.insert(a1);
    l2.insert(a1c);
    l1.insert(a2);
    l2.insert(a3c);
    std::cout << (l1 == l2) << std::endl;

    return 0;
}