#include <iostream>
#include <stdexcept>

// Учебный MyVector<T> — упрощённая модель std::vector.

template <typename T>
class MyVector {
private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void reallocate(std::size_t new_cap) {
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    MyVector() = default;

    ~MyVector() {
        delete[] data_;
    }

    // Запрещаем копирование для простоты
    MyVector(const MyVector&) = delete;
    MyVector& operator=(const MyVector&) = delete;

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void clear() { size_ = 0; }
};

int main() {
    MyVector<int> v;

    std::cout << "size = " << v.size()
              << ", capacity = " << v.capacity() << "\n";

    for (int i = 1; i <= 10; ++i) {
        v.push_back(i * 10);
        std::cout << "push_back(" << i * 10 << "): size = " << v.size()
                  << ", capacity = " << v.capacity() << "\n";
    }

    std::cout << "\nЭлементы: ";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
