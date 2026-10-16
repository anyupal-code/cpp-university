#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

// Задача 2. Класс Matrix.

class Matrix {
    std::size_t rows_, cols_;
    std::vector<std::vector<double>> data_;

public:
    Matrix(std::size_t rows, std::size_t cols, double init = 0.0)
        : rows_(rows), cols_(cols),
          data_(rows, std::vector<double>(cols, init)) {}

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }

    double& operator()(std::size_t i, std::size_t j) {
        if (i >= rows_ || j >= cols_) throw std::out_of_range("index");
        return data_[i][j];
    }

    const double& operator()(std::size_t i, std::size_t j) const {
        if (i >= rows_ || j >= cols_) throw std::out_of_range("index");
        return data_[i][j];
    }

    Matrix operator+(const Matrix& o) const {
        if (rows_ != o.rows_ || cols_ != o.cols_)
            throw std::invalid_argument("размеры не совпадают");
        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < rows_; ++i)
            for (std::size_t j = 0; j < cols_; ++j)
                result(i, j) = (*this)(i, j) + o(i, j);
        return result;
    }

    Matrix operator*(const Matrix& o) const {
        if (cols_ != o.rows_)
            throw std::invalid_argument("размеры несовместимы");
        Matrix result(rows_, o.cols_);
        for (std::size_t i = 0; i < rows_; ++i)
            for (std::size_t j = 0; j < o.cols_; ++j)
                for (std::size_t k = 0; k < cols_; ++k)
                    result(i, j) += (*this)(i, k) * o(k, j);
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (std::size_t i = 0; i < rows_; ++i)
            for (std::size_t j = 0; j < cols_; ++j)
                result(j, i) = (*this)(i, j);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (std::size_t i = 0; i < m.rows_; ++i) {
        os << "  [";
        for (std::size_t j = 0; j < m.cols_; ++j) {
            os << std::setw(6) << m(i, j);
        }
        os << " ]\n";
    }
    return os;
}

int main() {
    Matrix a(2, 3);
    a(0, 0) = 1; a(0, 1) = 2; a(0, 2) = 3;
    a(1, 0) = 4; a(1, 1) = 5; a(1, 2) = 6;

    std::cout << "A (2x3):\n" << a;

    Matrix b(2, 3);
    b(0, 0) = 10; b(0, 1) = 20; b(0, 2) = 30;
    b(1, 0) = 40; b(1, 1) = 50; b(1, 2) = 60;

    std::cout << "\nB (2x3):\n" << b;

    std::cout << "\nA + B:\n" << (a + b);

    std::cout << "\nAᵀ (3x2):\n" << a.transpose();

    std::cout << "\nAᵀ * A (3x3):\n" << (a.transpose() * a);

    return 0;
}