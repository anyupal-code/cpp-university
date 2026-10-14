#include <iostream>
#include <vector>

// Задача 4. Решето Эратосфена.
// Все простые числа до N (включительно).

std::vector<int> sieve(int n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            // вычёркиваем кратные i, начиная с i*i
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

int main() {
    int n;
    std::cout << "N = ";
    std::cin >> n;

    auto primes = sieve(n);

    std::cout << "Простых чисел до " << n << ": " << primes.size() << "\n";
    std::cout << "Первые 20: ";
    for (int i = 0; i < 20 && i < static_cast<int>(primes.size()); ++i) {
        std::cout << primes[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
