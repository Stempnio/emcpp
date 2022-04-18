#pragma include once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix{

	T data[N*M];

 public:

    constexpr size_t numberOfRows() const { return N; }
    constexpr size_t numberOfColumns() const { return M; }
	
	explicit Matrix(int nrows=N, int ncols=M){
	  std::fill_n(data, N*M, T{});
	}
    Matrix(const std::initializer_list<std::initializer_list<T>> & list){
		T * p = data;
		for(const auto & row: list){
	  		T* p2 = std::copy(row.begin(), row.end(), p);
	  		std::fill(p2, p+=M, T{});
		}
    }

	Matrix(const Matrix & m) {
		std::copy_n(m.data, N*M, data);
	}
	
	Matrix & operator= (const Matrix & m) {
		if(&m != this){
			std::copy_n(m.data, N*M, data);
		}
		return *this;
	}

	T& operator()(int i, int j)  {
	   return data[(i-1)*M+j-1];
	}

    const T& operator()(int i, int j) const {
        return data[(i-1)*M+j-1];
    }

    constexpr friend Matrix operator+( const Matrix & a, const Matrix &b) {
		Matrix r;
		for(int i = 1; i <= N; ++i){
			for(int j = 1; j <= M; ++j){
				r(i,j) = a(i,j) + b(i,j) ;
			}
		}
		return r;
	}

    template<typename Matrix>
    class iterator {
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        iterator(PointerType ptr) : ptr(ptr) {}

        iterator& operator++() {
            ptr++;
            return *this;
        }

        iterator operator++(int) {
            auto iterator = *this;
            ++(*this);
            return iterator;
        }

        PointerType operator->() {
            return ptr;
        }

        ReferenceType operator*() {
            return *ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

    private:
        PointerType ptr;
    };

    template<typename Matrix>
    class const_iterator {
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        const_iterator(PointerType ptr) : ptr(ptr) {}

        const_iterator& operator++() {
            ptr++;
            return *this;
        }

        const_iterator operator++(int) {
            auto iterator = *this;
            ++(*this);
            return iterator;
        }

        const PointerType operator->() const {
            return ptr;
        }

        const ReferenceType operator*() const {
            return *ptr;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

    private:
        PointerType ptr;
    };



    template<typename Matrix>
    class row_iterator {
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        row_iterator(PointerType ptr) : ptr(ptr) {}

        row_iterator& operator++() {
            ptr++;
            return *this;
        }

        row_iterator operator++(int) {
            auto iterator = *this;
            ++(*this);
            return iterator;
        }

        PointerType operator->() {
            return ptr;
        }

        ReferenceType operator*() {
            return *ptr;
        }

        bool operator==(const row_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const row_iterator& other) const {
            return ptr != other.ptr;
        }

    private:
        PointerType ptr;
    };


    template<typename Matrix>
    class col_iterator {
    public:
        using ValueType = typename Matrix::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        col_iterator(PointerType ptr) : ptr(ptr) {}

        col_iterator& operator++() {
            ptr+=M;
            return *this;
        }

        col_iterator operator++(int) {
            auto iterator = *this;
            ++(*this);
            return iterator;
        }

        PointerType operator->() {
            return ptr;
        }

        ReferenceType operator*() {
            return *ptr;
        }

        bool operator==(const col_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const col_iterator& other) const {
            return ptr != other.ptr;
        }

    private:
        PointerType ptr;
    };

    using ValueType = T;
    using Iterator = iterator<Matrix<T,N,M>>;
    using ConstIterator = const_iterator<Matrix<T,N,M>>;
    using RowIterator = row_iterator<Matrix<T,N,M>>;
    using ColIterator = col_iterator<Matrix<T,N,M>>;

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data+N*M);
    }

    ConstIterator begin() const {
        return ConstIterator(data);
    }

    ConstIterator end() const {
        return ConstIterator(data+N*M);
    }

    RowIterator row_begin(unsigned n) {
        n-=1;
        return RowIterator(data+n*M);
    }

    RowIterator row_end(unsigned n) {
        n-=1;
        return RowIterator(data+(n+1)*M);
    }

    ColIterator col_begin(unsigned n) {
        n-=1;
        return ColIterator(data+n);
    }

    ColIterator col_end(unsigned n) {
        n-=1;
        return ColIterator(data + N*M + n);
    }


};

template <typename T, size_t N, size_t M>
constexpr void printMatrix(const Matrix<T,N,M> & m, int width = 10){
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1) 
				cout << " ";
			cout << setw(width) <<  m(i,j) ;
		}
		cout << endl;
	}
}
