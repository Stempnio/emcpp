#ifndef STATICCONTAINER_H_STATICVECTOR_H
#define STATICCONTAINER_H_STATICVECTOR_H

template<typename T, unsigned N>
class Vector {
    T coef[N];

    Vector(T coef[]) {
        for(auto i=0; i<N; i++)
            this->coef[i] = coef[i];
    }

public:
    Vector() {
        for(auto i=0; i<N; i++)
            coef[i] = 0;
    }

    Vector(const Vector& v) = default;

    Vector(const std::initializer_list<T> list) {
        std::copy(list.begin(), list.end(), coef);
    }

    template<typename S>
    explicit Vector(const Vector<S,0>& v) {
        for(auto i=0; i<N; i++)
            this->coef[i] = v[i];
    }

    template<typename S, unsigned M>
    explicit Vector(const Vector<S,M>& v) {
        for(auto i=0; i<M; i++)
            this->coef[i] = v[i];
    }


    T& operator [](unsigned pos) {
        return coef[pos];
    }

    const T& operator [](unsigned pos) const {
        return coef[pos];
    }

    Vector<T,N> operator+(Vector<T,0>& v) {
        T newArr[N];
        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(newArr);
    }

    Vector<T,N> operator+(Vector<T,0>& v) const {
        T newArr[N];
        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(newArr);
    }

    Vector operator+(Vector& v) {
        T newArr[N];
        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(newArr);
    }

    Vector operator+(Vector v) const {
        T newArr[N];
        for(auto i=0; i<N; i++)
            newArr[i] = coef[i] + v[i];

        return Vector(newArr);
    }

    typedef T value_type;

//    unsigned size() {
//        return N;
//    }

    unsigned size() const {
        return N;
    }

    friend std::ostream& operator<< (std::ostream& out, const Vector& v) {
        for(auto x : v.coef) {
            out << x << " ";
        }
        return out;
    }

};

#endif //STATICCONTAINER_H_STATICVECTOR_H
