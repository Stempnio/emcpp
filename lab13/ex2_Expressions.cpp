#include <iostream>

template<unsigned N, typename T>
constexpr T ScalarProduct(T a[], T b[]) {
    if constexpr (N > 0) {
        return a[N-1]*b[N-1] + ScalarProduct<N-1, T>(a,b);
    } else {
        return 0;
    }
}

template<unsigned N, unsigned M, typename T>
constexpr void Multiply(T A[], T x[], T y[]) {
    if constexpr(N > 0) {
        y[N-1] = ScalarProduct<M, T>(A + (N-1)*M, x);
        Multiply<N-1,M,T>(A,x,y);
    }
}


int main() {

    double a[] = {1, 2, 3};
    double b[] = {1, 1, 1};
    std::cout<< ScalarProduct<3>(a, b) << '\n'; // 6

    double x[] = {1, 1, 0};
    double A[] = {1, 0, 0,
                  2, -5, 1};
    double y[2];
    Multiply<2,3>(A, x, y);
    std::cout << y[0] << " " << y[1];  // 1 -3

}
