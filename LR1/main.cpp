#include "Map.hpp"
#include <iostream>
#include <iomanip>

int main() {
    Map<int,int> A;
    List<int> keyslist, valueslist;
    A.insert(10,5);
    A.insert(5,5);
    A.insert(35,5);
    A.insert(7,5);
    A.insert(8,5);
    A.insert(12,5);
    A.insert(15,5);
    A.insert(18,5);
    A.insert(23,5);
    A.insert(11,5);
    for (int i=0;i>-10;i--) {
        A.insert(i,5);
    }
    keyslist=A.get_keys();
    valueslist=A.get_values();
    while (!keyslist.isLast()) {
        std::cout.width(4);
        std::cout<<keyslist.current();
        keyslist.go_next();
    }
    std::cout.width(4);
    std::cout<<keyslist.current()<<'\n';
    while (!valueslist.isLast()) {
        std::cout.width(4);
        std::cout<<valueslist.current();
        valueslist.go_next();
    }
    std::cout.width(4);
    std::cout<<valueslist.current()<<'\n';
    A.printTree();
    A.remove(7);
    A.remove(-5);
    A.remove(35);
    A.printTree();
    }
