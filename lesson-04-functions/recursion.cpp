#include <iostream>

// Рекурсия: факториал, Фибоначчи, быстрая степень.

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

long long fast_pow(long long base, int exp) {
    if (exp == 0) return 1;
    if (exp % 2 == 0) {
        long long half = fast_pow(base, exp / 2);
        return half * half;
    }
    return base * fast_pow(base, exp - 1);
}

int main() {
    std::cout << "=== Факториал ===\n";
    for (int i = 0; i <= 10; ++i) {
        std::cout << i << "! = " << factorial(i) << "\n";
    }

    std::cout << "\n=== Фибоначчи ===\n";
    for (int i = 0; i <= 15; ++i) {
        std::cout << fib(i) << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Быстрая степень ===\n";
    std::cout << "2^10 = " << fast_pow(2, 10) << "\n";
    std::cout << "3^5  = " << fast_pow(3, 5) << "\n";
    std::cout << "5^0  = " << fast_pow(5, 0) << "\n";

    return 0;
}