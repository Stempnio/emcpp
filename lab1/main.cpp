#include <iostream>
#include <utility>

class Matrix {

public:
    unsigned N = 0;
    unsigned M = 0;
    double * data = nullptr;

    Matrix() = default;

    Matrix(unsigned N, unsigned M): N(N), M(M), data(new double[N*M]) {
        std::fill(data, data+N*M, 0.0);
        std::cout << "constructor of " << N << "x" << M << " matrix\n";
    }

    Matrix(const Matrix & matrix): N(matrix.N), M(matrix.M), data(new double[N*M]) {

        memcpy(data, matrix.data, N*M*sizeof(matrix.data));
        std::cout << "copy constructor of " << N << "x" << M << " matrix\n";
    }

    Matrix(Matrix&& other) noexcept {

        delete [] data;

        data = other.data;
        N = other.N;
        M = other.M;

        other.data = nullptr;
        other.N = 0;
        other.M = 0;
        std::cout << "move constructor of " << N << "x" << M << " matrix\n";
    }

    Matrix(const std::initializer_list<std::initializer_list<double>> & values) {
        size_t maxRow = 0;

        for(const auto & row : values) {
            maxRow = std::max(maxRow, row.size());
        }

        N = values.size();
        M = maxRow;

        data = new double[N*M];

        double* p = data;
        for(const auto & row : values) {
            auto last = std::copy(row.begin(), row.end(), p);
            std::fill(last, p+M, 0.0);
            p += M;
        }

        std::cout << "list initializer constructor of " << N << "x" << M << " matrix\n";
    }

    double operator()(unsigned row, unsigned column) const {
        auto index = (row-1)*M + (column-1);

        return index < N*M ? data[index] : 0.0;
    }

    Matrix& operator=(const Matrix& other) {

        if(this == &other)
            return *this;

        M = other.M;
        N = other.N;

        delete [] data;
        data = nullptr;
        data = new double(N*M);

        memcpy(data, other.data, N*M*sizeof(other.data));
        std::cout << "copy assignment operator\n";
        return *this;
    }

    Matrix& operator=(Matrix&& other)  noexcept {

        if(this == &other)
            return *this;

        delete [] data;

        data = other.data;
        N = other.N;
        M = other.M;

        other.data = nullptr;
        other.N = 0;
        other.M = 0;
        std::cout << "move assignment operator\n";

        return *this;
    }

    Matrix operator-() const {
        Matrix m(N, M);
        auto size = N*M;
        for(auto i = 0; i<size; i++) {
            m.data[i] = data[i]*(-1);
        }
        return m;
    }

    friend std::ostream & operator<<(std::ostream & out, const Matrix & matrix) {
        auto size = matrix.M*matrix.N;

        if(size == 0) {
            out << "{ }";
            return out;
        }

        std::string result;
        out << "{ ";
        for(auto i=0; i<size; i++) {
            out << std::to_string(matrix.data[i]);
            out << " ";
            if((i+1) % matrix.M == 0) {
                out << "}";
                out << std::endl;
                if((i+1) < size)
                    out << "{ ";
            }
        }
        return out;
    }

    ~Matrix() {
        //std::cout << "destructor of " << N << "x" << M << " matrix\n";
        delete [] data;
        data = nullptr;
    }
};

class MatrixWithLabel : public Matrix {
    std::string label = "A";

public:
    using Matrix::Matrix;

    MatrixWithLabel(std::string label, unsigned numberOfRows, unsigned numberOfColumns) :
        label(std::move(label)),
        Matrix(numberOfRows, numberOfColumns) {}

    MatrixWithLabel(std::string label, const std::initializer_list<std::initializer_list<double>> & values) :
        label(std::move(label)),
        Matrix(values) {}

    // after writing own copy constructor default move constructor stops working
    MatrixWithLabel(const MatrixWithLabel& other) :
        label(other.label),
        Matrix(other) {}

    // after adding default move constructor and assignment operators everything works
    MatrixWithLabel(MatrixWithLabel&& other) = default;

    MatrixWithLabel& operator=(const MatrixWithLabel& other) = default;

    MatrixWithLabel& operator=(MatrixWithLabel&& other) = default;


    std::string getLabel() {
        return label;
    }

    void setLabel(std::string newLabel) {
        this->label = std::move(newLabel);
    }

};

int main() {
    Matrix m1;
    Matrix m2(3,4);
    Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
    std::cout << m2(1,1) << std::endl;  // 0
    std::cout << m3(2,2) << std::endl;  // 23
    std::cout << m3;

    std::cout << "Copy semantics \n";
    Matrix m4 = m2;
    m4 = m3;

    std::cout << "Move semantics \n";
    Matrix m7 = std::move(m2);
    m4 = -m3;

    std::cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix * pm = new Matrix(-m4);
    std::cout << m6(2,1) << std::endl; // 32

    std::cout << "Inheritance \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1({{1,2},{4,5}});
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = std::move(l1);
    std::cout << l2.getLabel() << " " << l3.getLabel() << std::endl;
    // 	cout << l1.getLabel() << endl;


    return 0;
}
