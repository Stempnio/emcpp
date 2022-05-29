#include <iostream>
#include "TypeCheck.cpp"
#include <vector>

namespace v1 {

    template<typename T>
    std::enable_if_t<hasSize_v<T> && hasValueType_v<T>, size_t>
    getSize(const T& x) {
        return x.size() * sizeof (typename T::value_type);
    }

    template<typename T>
    std::enable_if_t<!(hasSize_v<T> && hasValueType_v<T>), size_t>
    getSize(const T& x) {
        return sizeof (x);
    }
}

namespace v2 {

    template<typename T>
    size_t getSize(const T& x) {
        if constexpr (hasSize_v<T> && hasValueType_v<T>)
            return x.size() * sizeof (typename T::value_type);
        else
            return sizeof (x);
    }
}

int main() {
    std::vector<int> v{1,2,3,4,5};
    std::cout << v1::getSize(5) << std::endl;  // 4
    std::cout << v1::getSize(v) << std::endl; // 20
    std::cout << v2::getSize(5) << std::endl;  // 4
    std::cout << v2::getSize(v) << std::endl; // 20

}