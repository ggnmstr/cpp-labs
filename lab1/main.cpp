#include "linkedhashset.hpp"
#include <iostream>
int main(){
    linkedhs<int> l1;
    l1.insert(2);
    l1.insert(1);
    l1.insert(52);
    l1.insert(52);
    l1.remove(1);
    for (auto i : l1){
        std::cout << i << std::endl;
    }
    return 0;
}