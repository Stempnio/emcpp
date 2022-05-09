
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "VectorTraits.cpp"

template <typename T, size_t N, typename P>
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

  Vector() {
      P::init(data, N);
  }
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
      P::init_initializer_list(list, N);
      std::copy(list.begin(), list.end(), data);
  }

  size_type size() const {
	return N;
  }

  arg_type get(size_type index) const {
      P::check(index, N);
      return data[index];
  }

  void set(size_type index, arg_type value) {
      P::check(index, N);
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