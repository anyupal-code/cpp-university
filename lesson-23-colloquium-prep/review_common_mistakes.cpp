#include <iostream>
#include <string>
#include <memory>

// Обзор: типичные ошибки и их исправления.

// === ОШИБКА 1: не виртуальный деструктор ===
// Плохо:
class BadBase1 {
public:
    ~BadBase1() { std::cout << "  ~BadBase1\n"; }
};

class BadDerived1 : public BadBase1 {
    int* data_;
public:
    BadDerived1() : data_(new int[10]) {}
    ~BadDerived1() {
        delete[] data_;
        std::cout << "  ~BadDerived1\n";
    }
};

// Хорошо:
class GoodBase1 {
public:
    virtual ~GoodBase1() { std::cout << "  ~GoodBase1\n"; }
};

class GoodDerived1 : public GoodBase1 {
    int* data_;
public:
    GoodDerived1() : data_(new int[10]) {}
    ~GoodDerived1() override {
        delete[] data_;
        std::cout << "  ~GoodDerived1\n";
    }
};

// === ОШИБКА 2: срезка ===
class Base2 {
public:
    virtual std::string name() const { return "Base"; }
    virtual ~Base2() = default;
};

class Derived2 : public Base2 {
public:
    std::string name() const override { return "Derived"; }
};

void bad_by_value(Base2 b) {
    std::cout << "  плохо (по значению): " << b.name() << "\n";
}

void good_by_ref(const Base2& b) {
    std::cout << "  хорошо (по ссылке): " << b.name() << "\n";
}

// === ОШИБКА 3: использование после move ===
void move_mistake() {
    auto p = std::make_unique<int>(42);
    auto q = std::move(p);

    // p теперь nullptr
    if (p == nullptr) {
        std::cout << "  правильно: не использовать p после move\n";
    }
}

// === ОШИБКА 4: компаратор с <= ===
// Плохо: [](int a, int b) { return a <= b; }  — UB!
// Хорошо: [](int a, int b) { return a < b; }

int main() {
    std::cout << "=== Ошибка 1: деструктор ===\n";
    std::cout << "Без virtual:\n";
    {
        BadBase1* p = new BadDerived1;
        delete p;   // ~BadDerived1 НЕ вызовется — утечка data_
    }

    std::cout << "\nС virtual:\n";
    {
        GoodBase1* p = new GoodDerived1;
        delete p;   // всё корректно
    }

    std::cout << "\n=== Ошибка 2: срезка ===\n";
    Derived2 d;
    bad_by_value(d);
    good_by_ref(d);

    std::cout << "\n=== Ошибка 3: после move ===\n";
    move_mistake();

    std::cout << "\n=== Ошибка 4: компаратор ===\n";
    std::cout << "  Всегда используйте < (не <=)\n";
    std::cout << "  Иначе std::sort может дать UB\n";

    return 0;
}