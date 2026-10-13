#include <iostream>
#include <string>

// Передача параметров: по значению, по ссылке, по константной ссылке.

// По значению — копия, оригинал не меняется
void bad_inc(int x) {
    ++x;   // меняется только локальная копия
}

// По ссылке — меняет оригинал
void good_inc(int& x) {
    ++x;
}

// По константной ссылке — не копирует, не меняет
void print_string(const std::string& s) {
    std::cout << "Строка: " << s << "\n";
}

// Через указатель — тоже меняет оригинал
void inc_ptr(int* p) {
    ++(*p);
}

int main() {
    int a = 5;

    bad_inc(a);
    std::cout << "после bad_inc:  a = " << a << " (не изменилось)\n";

    good_inc(a);
    std::cout << "после good_inc: a = " << a << "\n";

    inc_ptr(&a);
    std::cout << "после inc_ptr:  a = " << a << "\n";

    std::string s = "Hello, World!";
    print_string(s);

    return 0;
}