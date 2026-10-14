#include <iostream>
#include <vector>

// Перегрузка [], (), ->.

class MyArray {
private:
    std::vector<int> data_;

public:
    MyArray(std::size_t n, int init = 0) : data_(n, init) {}

    // Для изменения
    int& operator[](std::size_t i) {
        return data_[i];
    }

    // Для чтения из const-объекта
    const int& operator[](std::size_t i) const {
        return data_[i];
    }

    std::size_t size() const { return data_.size(); }
};

class Multiplier {
private:
    int factor_;

public:
    Multiplier(int f) : factor_(f) {}

    int operator()(int x) const {
        return x * factor_;
    }
};

class Counter {
private:
    int count_ = 0;

public:
    Counter& operator++() {
        ++count_;
        return *this;
    }

    int value() const { return count_; }
};

int main() {
    std::cout << "=== operator[] ===\n";
    MyArray a(5);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = static_cast<int>(i * 10);
    }
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "=== operator() — функтор ===\n";
    Multiplier triple(3);
    std::cout << "triple(5)  = " << triple(5) << "\n";
    std::cout << "triple(10) = " << triple(10) << "\n\n";

    std::cout << "=== operator++ ===\n";
    Counter c;
    ++c; ++c; ++c;
    std::cout << "c.value() = " << c.value() << "\n";

    return 0;
}
