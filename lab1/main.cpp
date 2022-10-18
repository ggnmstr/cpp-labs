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
    l1.insert(a2);
    l1.insert(a3);
    l2.insert(a4);
    l2.insert(a5);
    //std::cout << l1.contains(a3) << std::endl;
    //std::cout << l2.contains(a5) << std::endl;
    //l1.swap(l2);
    //std::cout << l1.contains(a3) << std::endl;
    //std::cout << l2.contains(a5) << std::endl;
    //std::cout << l1.contains(a5) << std::endl;
    //std::cout << l2.contains(a3) << std::endl;
    linkedhs l3(l2);
    std::cout << l3.contains(a4) << std::endl;
    std::cout << l3.contains(a5) << std::endl;
    l2.remove(a4);
    l3.remove(a5);
    std::cout << l3.contains(a4) << std::endl;
    std::cout << l3.contains(a5) << std::endl;
    //l3 = l2;
    l1.clear();
    //std::cout << l3.contains(a4) << std::endl;
    //std::cout << l3.contains(a5) << std::endl;

    return 0;
}