#include <iostream>
#include <string>
#include <cstring>

// const_cast и mutable.

// Старый C-API, который не принимает const
void old_c_function(char* s) {
    std::cout << "  old_c_function получил: \"" << s << "\"\n";
    // В этом API мы обещаем не менять s
}

class Cache {
    mutable int cached_value_ = 0;
    mutable int calls_ = 0;

public:
    int compute(int x) const {
        ++calls_;                 // ok: mutable
        cached_value_ = x * 2;
        return cached_value_;
    }

    int calls() const { return calls_; }
};

class Temperature {
    mutable double cached_celsius_ = 0;
    mutable bool valid_ = false;
    double fahrenheit_;

public:
    explicit Temperature(double f) : fahrenheit_(f) {}

    double celsius() const {
        if (!valid_) {
            cached_celsius_ = (fahrenheit_ - 32) * 5 / 9;
            valid_ = true;
        }
        return cached_celsius_;
    }
};

int main() {
    std::cout << "=== const_cast для C-API ===\n";
    const char* s = "Hello";
    old_c_function(const_cast<char*>(s));

    std::cout << "\n=== ОПАСНО: изменение const ===\n";
    const int x = 42;
    int& ref = const_cast<int&>(x);
    // ref = 100;    // UB! Не делаем этого
    std::cout << "  const_cast использован только для чтения\n";
    std::cout << "  x = " << x << ", ref = " << ref << "\n";

    std::cout << "\n=== mutable ===\n";
    const Cache c;
    std::cout << "  compute(10) = " << c.compute(10) << "\n";
    std::cout << "  compute(20) = " << c.compute(20) << "\n";
    std::cout << "  calls = " << c.calls() << "\n";

    const Temperature t(212);
    std::cout << "\n  Fahrenheit: 212\n";
    std::cout << "  Celsius: " << t.celsius() << "\n";
    std::cout << "  Celsius снова (кэш): " << t.celsius() << "\n";

    return 0;
}