#include <iostream>
#include <string>

// Обзор всех четырёх кастов.

class Base {
public:
    virtual ~Base() = default;
    virtual std::string name() const { return "Base"; }
};

class Derived : public Base {
public:
    std::string name() const override { return "Derived"; }
    void only_derived() const {
        std::cout << "    только Derived\n";
    }
};

int main() {
    std::cout << "=== static_cast: числа ===\n";
    double d = 3.14;
    int i = static_cast<int>(d);
    std::cout << "  static_cast<int>(3.14) = " << i << "\n";
    std::cout << "  static_cast<double>(7) = " << static_cast<double>(7) << "\n\n";

    std::cout << "=== static_cast: вверх по иерархии ===\n";
    Derived d_obj;
    Base* b = static_cast<Base*>(&d_obj);   // безопасно
    std::cout << "  Base* -> name(): " << b->name() << "\n\n";

    std::cout << "=== dynamic_cast: вниз с проверкой ===\n";
    Base* base = new Derived;
    if (auto* der = dynamic_cast<Derived*>(base)) {
        std::cout << "  dynamic_cast успешно:\n";
        der->only_derived();
    } else {
        std::cout << "  не Derived\n";
    }
    delete base;

    std::cout << "\n=== const_cast ===\n";
    const int x = 42;
    int& y = const_cast<int&>(x);
    // y = 100;   // UB: x изначально const
    std::cout << "  const_cast использован для чтения: y = " << y << "\n\n";

    std::cout << "=== reinterpret_cast ===\n";
    int value = 0x12345678;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    std::cout << "  Байты int 0x12345678: ";
    for (std::size_t i = 0; i < sizeof(int); ++i) {
        std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << "\n";

    return 0;
}