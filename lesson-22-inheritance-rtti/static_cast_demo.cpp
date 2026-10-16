#include <iostream>

// static_cast vs dynamic_cast.

class Base {
public:
    virtual ~Base() = default;
    virtual void print() const {
        std::cout << "Base\n";
    }
};

class DerivedA : public Base {
public:
    void print() const override {
        std::cout << "DerivedA\n";
    }
    void only_a() const {
        std::cout << "  метод только A\n";
    }
};

class DerivedB : public Base {
public:
    void print() const override {
        std::cout << "DerivedB\n";
    }
};

int main() {
    std::cout << "=== static_cast: без проверки ===\n";
    Base* b1 = new DerivedA;

    DerivedA* da = static_cast<DerivedA*>(b1);   // ок — тип правильный
    da->only_a();

    DerivedB* db = static_cast<DerivedB*>(b1);   // НЕ проверит!
    std::cout << "static_cast<DerivedB*>: указатель получен, но...\n";
    std::cout << "  (если вызвать db->only_b() — UB!)\n\n";

    delete b1;

    std::cout << "=== dynamic_cast: с проверкой ===\n";
    Base* b2 = new DerivedA;

    if (auto* a = dynamic_cast<DerivedA*>(b2)) {
        std::cout << "Приведение к DerivedA успешно\n";
        a->only_a();
    }

    if (auto* bb = dynamic_cast<DerivedB*>(b2)) {
        std::cout << "Приведение к DerivedB успешно\n";
    } else {
        std::cout << "Приведение к DerivedB: nullptr (не тот тип)\n";
    }

    delete b2;

    return 0;
}