
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

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

template <typename T, size_t N >
class Vector {
  T data[N];
 public:
  typedef T value_type;
  typedef std::size_t  size_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;

  typedef typename vector_traits<T>::scalar scalar;
  typedef typename vector_traits<T>::arg_type arg_type;

  Vector() = default;
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
	std::copy(list.begin(), list.end(), data);
  }
  size_type size() const {
	return N;
  }

  arg_type get(size_type index) const {
	return data[index];
  }

  void set(size_type index, arg_type value) {
	data[index] = value;
  }

  friend Vector operator* (const scalar x, const Vector & v ){
	Vector result;
	for(int i=0; i < v.size(); ++i){
	  result.set(i, vector_traits<T>::mul(x, v.get(i)));
	}
	return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
	for(int i=0; i < v.size(); ++i){
	  out << v.get(i) << " ";
	}
	return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
	Vector::value_type value;
	for(int i=0; i < v.size(); ++i){
	  in >> value;
	  if(in)
		v.set(i, value);
	}
	return in;
  }

};

#endif // LAB8_VECTOR_H