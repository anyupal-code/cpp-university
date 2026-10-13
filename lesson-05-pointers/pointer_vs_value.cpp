#include <iostream>

// Разница между передачей по значению и через указатель.

void by_value(int x) {
    x = 100;
    std::cout << "  внутри by_value: x = " << x << "\n";
}

void by_pointer(int* p) {
    *p = 100;
    std::cout << "  внутри by_pointer: *p = " << *p << "\n";
}

void by_reference(int& x) {
    x = 100;
    std::cout << "  внутри by_reference: x = " << x << "\n";
}

int main() {
    int a = 5;

    std::cout << "a = " << a << "\n";
    by_value(a);
    std::cout << "после by_value:    a = " << a << " (не изменилось)\n\n";

    by_pointer(&a);
    std::cout << "после by_pointer:  a = " << a << "\n\n";

    a = 5;
    by_reference(a);
    std::cout << "после by_reference: a = " << a << "\n";

    return 0;
}
