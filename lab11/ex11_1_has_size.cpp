#include <iostream>
#include <vector>
#include "TypeCheck.cpp"

int main() {
    std::cout << hasSize< int >::value << std::endl; // false
    std::cout << hasSize<std::vector<int> >::value << std::endl; //true
    std::cout << hasValueType< int >::value << std::endl; // false
    std::cout << hasValueType<std::vector<int>>::value << std::endl; //true
}