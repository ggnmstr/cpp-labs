#include "linkedhashset.h"
#include <iostream>
int main(){
    linkedhs<int> l1;
    l1.insert(1);
    l1.insert(2);
    l1.insert(3);
    for (auto i : l1){
        std::cout << i << std::endl;
    }
    return 0;
}