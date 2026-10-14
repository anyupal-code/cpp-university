#include <iostream>
#include <string>

// Способы передачи: значение, ссылка, const-ссылка.

struct Big {
    std::string data;

    Big(const std::string& s) : data(s) {
        std::cout << "  [Big ctor]\n";
    }

    Big(const Big& o) : data(o.data) {
        std::cout << "  [Big copy ctor]\n";
    }
};

void by_value(Big b) {
    std::cout << "    by_value: " << b.data << "\n";
}

void by_ref(Big& b) {
    b.data += "!";
    std::cout << "    by_ref: " << b.data << "\n";
}

void by_cref(const Big& b) {
    std::cout << "    by_cref: " << b.data << "\n";
}

int main() {
    Big b("Hello");

    std::cout << "by_value:\n";
    by_value(b);

    std::cout << "\nby_cref:\n";
    by_cref(b);

    std::cout << "\nby_ref:\n";
    by_ref(b);
    std::cout << "  b теперь: " << b.data << "\n";

    return 0;
}
