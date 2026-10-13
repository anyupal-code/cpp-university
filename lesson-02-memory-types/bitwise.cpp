#include <iostream>
#include <format>

// Базовые битовые операции: &, |, ^, ~.

int main() {
    unsigned a = 12;   // 1100
    unsigned b = 10;   // 1010

    std::cout << std::format("a = {:>2} = {:04b}\n", a, a);
    std::cout << std::format("b = {:>2} = {:04b}\n", b, b);
    std::cout << "---\n";
    std::cout << std::format("a & b  = {:>2} = {:04b}\n", a & b, a & b);
    std::cout << std::format("a | b  = {:>2} = {:04b}\n", a | b, a | b);
    std::cout << std::format("a ^ b  = {:>2} = {:04b}\n", a ^ b, a ^ b);
    std::cout << std::format("~a     = {:>2} = {:032b}\n", ~a, ~a);

    return 0;
}
