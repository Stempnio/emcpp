#ifndef LAB8_VECTOR_POLICIES
#define LAB8_VECTOR_POLICIES

#include <memory>
#include <iostream>

class VectorException : public std::runtime_error {
public:
    explicit VectorException(const char*  msg) : runtime_error(msg) {}
};

class Policy {
public:
    template<typename T>
    static void init(T data[], size_t N) {}

    static void check(size_t pos,size_t N) {}

    template<typename T>
    static void init_initializer_list(const std::initializer_list<T> &list, size_t N) {}
};

class SafePolicy : public Policy {
public:
    template<typename T>
    static void init(T data[], size_t N) {
        for(auto i=0; i<N; i++) {
            data[i] = 0;
        }
    }

    template<typename T>
    static void init_initializer_list(const std::initializer_list<T> &list, size_t N) {
        if(list.size() != N) {
            throw VectorException("Initializer list size different than Vector's!");
        }
    }

    static void check(size_t pos, size_t N) {
        if(pos < 0 || pos >= N) {
            throw VectorException("Index out of bounds!");
        }
    }
};

typedef Policy FastPolicy;

class InitFastPolicy : public SafePolicy {
public:
    using Policy::check;

    using Policy::init_initializer_list;
};



#endif