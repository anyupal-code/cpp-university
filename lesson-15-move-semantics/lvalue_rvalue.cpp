#include <iostream>

// lvalue vs rvalue: категории значений.

int get_value() {
    return 42;   // возврат по значению — rvalue
}

int main() {
    int x = 5;

    // lvalue — имеет имя
    std::cout << "=== lvalue ===\n";
    std::cout << "x = " << x << "\n";
    std::cout << "&x = " << &x << " (можно взять адрес)\n";

    int* p = &x;
    std::cout << "*p = " << *p << "\n\n";

    // rvalue — временное
    std::cout << "=== rvalue ===\n";
    std::cout << "5          = " << 5 << "\n";
    std::cout << "x + 3      = " << x + 3 << "\n";
    std::cout << "get_value()= " << get_value() << "\n";

    // int* q = &5;   // ошибка: нельзя взять адрес у rvalue
    // int* q = &(x + 3);   // тоже ошибка

    // lvalue можно присваивать
    std::cout << "\n=== Присваивание ===\n";
    x = 10;             // x — lvalue, можно менять
    std::cout << "После x = 10: " << x << "\n";

    // 5 = 10;          // ошибка: rvalue нельзя присвоить

    // Ссылки
    std::cout << "\n=== Ссылки ===\n";
    int& lref = x;              // lvalue-ссылка
    lref = 20;
    std::cout << "Через lref: x = " << x << "\n";

    // int& lref2 = 5;          // ошибка: 5 — rvalue

    const int& cref = 5;        // const-ссылка может на rvalue
    std::cout << "const int& cref = 5: " << cref << "\n";

    return 0;
}