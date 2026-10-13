#include <iostream>

// Значения по умолчанию.

int power(int base, int exp = 2) {
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

void greet(const std::string& name, const std::string& greeting = "Привет") {
    std::cout << greeting << ", " << name << "!\n";
}

int main() {
    std::cout << "power(5)     = " << power(5) << "\n";       // 25
    std::cout << "power(2, 10) = " << power(2, 10) << "\n";    // 1024

    greet("Иван");
    greet("Мария", "Здравствуйте");

    return 0;
}
