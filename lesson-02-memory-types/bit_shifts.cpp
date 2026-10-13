#include <iostream>
#include <format>

// Сдвиги и работа с битами: проверка, установка, сброс, инверсия.

void print_bits(unsigned x) {
    std::cout << std::format("{:032b}\n", x);
}

bool is_bit_set(unsigned x, int pos) {
    return (x >> pos) & 1u;
}

int main() {
    std::cout << "=== Сдвиги ===\n";
    std::cout << "1 << 0  = " << (1u << 0) << "\n";
    std::cout << "1 << 1  = " << (1u << 1) << "\n";
    std::cout << "1 << 4  = " << (1u << 4) << "\n";
    std::cout << "1 << 10 = " << (1u << 10) << "\n";

    std::cout << "\n=== Работа с битами ===\n";
    unsigned x = 0b0000'1010;   // 10
    std::cout << "x = "; print_bits(x);

    // проверка
    std::cout << "бит 1 установлен? " << is_bit_set(x, 1) << "\n";
    std::cout << "бит 3 установлен? " << is_bit_set(x, 3) << "\n";

    // установка бита 3
    x |= (1u << 3);
    std::cout << "после установки бита 3: "; print_bits(x);

    // сброс бита 1
    x &= ~(1u << 1);
    std::cout << "после сброса бита 1:    "; print_bits(x);

    // инверсия бита 0
    x ^= (1u << 0);
    std::cout << "после инверсии бита 0:  "; print_bits(x);

    // проверка степени двойки
    unsigned p = 64;
    std::cout << "\n" << p << " — степень двойки? "
              << (p != 0 && (p & (p - 1)) == 0) << "\n";

    return 0;
}