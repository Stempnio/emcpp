#include <iostream>

// N ** M
template<int N, int M>
struct Power {
    static const int value = N * Power<N, M-1>::value;
};

template<int N>
struct Power<N, 1> {
    static const int value = N;
};

template<int N, int K>
struct Binomial {
    static const int value = Binomial<N-1,K>::value + Binomial<N-1,K-1>::value;
};

template<int N>
struct Binomial<N, N> {
    static const int value = 1;
};

template<int N>
struct Binomial<N, 0> {
    static const int value = 1;
};

int main() {

  std::cout << Power<5,3>::value << std::endl;   // 125
  static_assert( Power<5,3>::value == 125);
  static_assert( Power<2,8>::value == 256);

  std::cout << Binomial<4,2>::value << std::endl; //6
  std::cout << Binomial<100,0>::value << std::endl; //1
  std::cout << Binomial<100,1>::value << std::endl; //100
  std::cout << Binomial<100,6>::value << std::endl;
//  std::cout << Binomial<100,7>::value << std::endl; //16007560800
//
  static_assert( Binomial<4,2>::value == 6 );
  static_assert( Binomial<100,0>::value == 1 );
  static_assert( Binomial<100,1>::value == 100 );
//  static_assert( Binomial<100,7>::value == 16007560800 );

  return 0;
}
