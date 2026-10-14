#include <iostream>
#include <string>

// rvalue-ссылки и перегрузка по категории значения.

void f(int& x) {
    std::cout << "  f(int&) — lvalue\n";
}

void f(const int& x) {
    std::cout << "  f(const int&) — const lvalue или rvalue\n";
}

void f(int&& x) {
    std::cout << "  f(int&&) — rvalue\n";
}

std::string make_greeting() {
    return "Hello";
}

int main() {
    int a = 5;
    const int b = 10;

    std::cout << "f(a):              "; f(a);                // lvalue
    std::cout << "f(b):              "; f(b);                // const lvalue
    std::cout << "f(5):              "; f(5);                // rvalue
    std::cout << "f(a + 1):          "; f(a + 1);            // rvalue
    std::cout << "f(std::move(a)):   "; f(std::move(a));     // rvalue

    std::cout << "\n=== rvalue-ссылка напрямую ===\n";
    int&& rref = 100;
    std::cout << "rref = " << rref << "\n";
    rref = 200;
    std::cout << "rref = " << rref << " (можно менять)\n";

    std::cout << "\n=== rvalue-ссылка на временный объект ===\n";
    std::string&& s = make_greeting();
    std::cout << "s = " << s << "\n";
    s += ", World!";
    std::cout << "s = " << s << "\n";

    return 0;
}
