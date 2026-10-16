#include <iostream>
#include <cstdint>
#include <cstring>

// reinterpret_cast: переинтерпретация битов.

struct Point {
    int x, y;
};

int main() {
    std::cout << "=== Байты числа ===\n";
    uint32_t value = 0x12345678;

    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    std::cout << "  uint32_t 0x12345678 в байтах: ";
    for (std::size_t i = 0; i < sizeof(value); ++i) {
        std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << "\n";
    std::cout << "  (порядок зависит от архитектуры — little/big endian)\n\n";

    std::cout << "=== reinterpret_cast<Point*> ===\n";
    Point p{10, 20};
    int* as_int = reinterpret_cast<int*>(&p);
    std::cout << "  Point{10, 20} как int*: "
              << as_int[0] << " " << as_int[1] << "\n";
    std::cout << "  (работает, но не гарантированно переносимо)\n\n";

    std::cout << "=== uintptr_t ===\n";
    int x = 42;
    uintptr_t addr = reinterpret_cast<uintptr_t>(&x);
    std::cout << "  адрес x = " << std::hex << addr << std::dec << "\n";
    std::cout << "  (иногда используют для хешей указателей)\n\n";

    std::cout << "=== ПРЕДУПРЕЖДЕНИЕ ===\n";
    std::cout << "  reinterpret_cast — самый опасный каст.\n";
    std::cout << "  Используй только при работе с битами и C-API.\n";

    return 0;
}