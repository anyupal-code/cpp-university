#include <iostream>
#include <deque>
#include <string>

// Задача 1. Кольцевой буфер фиксированного размера.
// Добавляем в конец, при переполнении вытесняем с начала.

class RingBuffer {
private:
    std::deque<int> data_;
    std::size_t capacity_;

public:
    explicit RingBuffer(std::size_t cap) : capacity_(cap) {}

    void push(int value) {
        data_.push_back(value);
        if (data_.size() > capacity_) {
            data_.pop_front();
        }
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i + 1 < data_.size()) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    std::size_t size() const { return data_.size(); }
};

int main() {
    RingBuffer rb(3);

    std::cout << "Буфер размера 3\n\n";

    for (int x : {1, 2, 3, 4, 5, 6}) {
        rb.push(x);
        std::cout << "push(" << x << ") -> ";
        rb.print();
    }

    return 0;
}
