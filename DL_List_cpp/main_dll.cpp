#include "dl_list.hpp"

int main(){
    dll<int> l1(10);
    dll<int> l2;
    dll<string> l3;
    l1.push(8);
    l1.append(9);
    l1.reverse();
    l1.insert(2, 12);
    l2 = l1 + 2;
    l3.push("Mouad");
    l2.sort();
    l1.concatenate(l2);
    l1.print();
}