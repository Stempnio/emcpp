//
// Created by Jakub Stepien on 02/04/2022.
//

#ifndef STATICCONTAINER_H_DYNAMICVECTOR_H
#define STATICCONTAINER_H_DYNAMICVECTOR_H

#include "staticVector.h"
#include "iostream"

class VectorException : public std::runtime_error {
//    const char * message;
public:
//    VectorException(): std::runtime_error("incompatible sizes in Vector::operator+") {}
    VectorException(const char * message): std::runtime_error(message) {
//        this->message = message;
    }

//    const char * what() const noexcept override {
//        return message;
//    }
};

template<typename T>
class Vector<T, 0> {
    unsigned N;
    std::unique_ptr<T[]> coef = nullptr;

    Vector(std::unique_ptr<T[]> coef, unsigned n) {
        this->coef = std::move(coef);
        this->N = n;
    }
public:

    Vector(unsigned n): N(n), coef(std::make_unique<T[]>(N)) {
        for(auto i=0; i<n;i++)
            coef[i] = 0;
    }

    Vector(const Vector& v): N(v.N), coef(std::make_unique<T[]>(v.N)) {
        for(auto i=0; i<v.N; i++)
            this->coef[i] = v.coef[i];
    }

    Vector(const std::initializer_list<T> list) {
        coef = std::make_unique<T[]>(list.size());
        N = list.size();
        for(auto i=0; i < N; i++)
            this->coef[i] = *(list.begin()+i);
        this->N = list.size();
    }

    template<typename S, unsigned M>
    explicit Vector(const Vector<S,M>& v): N(M), coef(std::make_unique<T[]>(M)) {
        for(auto i=0; i<M; i++)
            this->coef[i] = v[i];
    }

    T& operator [](unsigned pos) {
        return coef[pos];
    }

    const T& operator [](unsigned pos) const {
        return coef[pos];
    }

    template<unsigned M>
    Vector<T,M> operator+(Vector<T,M>& v) {

        if(N != M) {
            throw VectorException("incompatible sizes in Vector::operator+");
        }

        auto tmp = Vector<T,M>();

        for(auto i=0; i<M; i++)
            tmp[i] = coef[i] + v[i];

        return tmp;
    }

    Vector operator+(Vector& v) {
        if(N != v.N) {
            throw VectorException("incompatible sizes in Vector::operator+");
        }
        auto newArr = std::make_unique<T[]>(N);

        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(std::move(newArr), N);
    }

    Vector operator+(Vector v) const {
        if(N != v.N) {
            throw VectorException("incompatible sizes in Vector::operator+");
        }
        auto newArr = std::make_unique<T[]>(N);

        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(std::move(newArr),N);
    }

    typedef T value_type;

//    unsigned size() {
//        return N;
//    }

    unsigned size() const {
        return N;
    }

    void resize(unsigned newSize) {
        auto newArr = std::make_unique<T[]>(newSize);

        if(newSize<N) {
            for(auto i=0; i<newSize; i++)
                newArr[i] = coef[i];
        } else if(newSize > N) {
            for(auto i=0; i<N; i++)
                newArr[i] = coef[i];

            for(auto i=N; i<newSize; i++)
                newArr[i] = 0;
        } else {
            return; // same size
        }

        std::swap(coef, newArr);
        this->N = newSize;
    }

    friend std::ostream& operator<< (std::ostream& out, const Vector& v) {
        for(auto i=0; i<v.N; i++) {
            out << v.coef[i] << " ";
        }
        return out;
    }
};

#endif //STATICCONTAINER_H_DYNAMICVECTOR_H
