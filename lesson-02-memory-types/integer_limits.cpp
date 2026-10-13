#include <iostream>
#include <limits>

// Диапазоны целых типов через std::numeric_limits.

int main() {
    std::cout << "=== int ===\n";
    std::cout << "max: " << std::numeric_limits<int>::max() << "\n";
    std::cout << "min: " << std::numeric_limits<int>::min() << "\n";

    std::cout << "\n=== unsigned int ===\n";
    std::cout << "max: " << std::numeric_limits<unsigned int>::max() << "\n";
    std::cout << "min: " << std::numeric_limits<unsigned int>::min() << "\n";

    std::cout << "\n=== long long ===\n";
    std::cout << "max: " << std::numeric_limits<long long>::max() << "\n";
    std::cout << "min: " << std::numeric_limits<long long>::min() << "\n";

    std::cout << "\n=== unsigned long long ===\n";
    std::cout << "max: " << std::numeric_limits<unsigned long long>::max() << "\n";

    return 0;
}