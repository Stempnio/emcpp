#ifndef LAB8_VECTOR_TRAITS
#define LAB8_VECTOR_TRAITS

#include <memory>
#include <iostream>

template<typename T>
class vector_traits_base {
public:
    typedef T value_type;
    typedef T scalar;
    typedef const T& arg_type;

    static value_type mul(scalar a, arg_type b) {
        return a*b;
    }

    static value_type default_value() {
        return 0;
    }
};

template<typename T>
class vector_traits : public vector_traits_base<T> {
};

template<>
class vector_traits<int> : public vector_traits_base<int> {
public:
    typedef int arg_type;
};

template<>
class vector_traits<double> : public vector_traits_base<double> {
public:
    typedef double arg_type;
};

template<>
class vector_traits<std::string> : public vector_traits_base<std::string> {
public:
    typedef int scalar;

    static value_type mul(scalar a, arg_type b) {
        value_type result;
        for(auto i=0; i< a; i++) {
            result += b;
        }

        return result;
    }

    static value_type default_value() {
        return "0";
    }
};

#endif