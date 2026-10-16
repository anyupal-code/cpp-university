#include <iostream>
#include <memory>

// Виртуальный деструктор: зачем нужен.

class Base {
public:
    Base()  { std::cout << "  Base()\n"; }
    ~Base() { std::cout << "  ~Base()\n"; }   // НЕ виртуальный!
};

class Derived : public Base {
    int* data_;
public:
    Derived() : data_(new int[100]) {
        std::cout << "  Derived() — выделено 100 int\n";
    }
    ~Derived() {
        delete[] data_;
        std::cout << "  ~Derived() — освобождено\n";
    }
};

// === С виртуальным деструктором ===

class VBase {
public:
    VBase()  { std::cout << "  VBase()\n"; }
    virtual ~VBase() { std::cout << "  ~VBase()\n"; }
};

class VDerived : public VBase {
    int* data_;
public:
    VDerived() : data_(new int[100]) {
        std::cout << "  VDerived() — выделено\n";
    }
    ~VDerived() override {
        delete[] data_;
        std::cout << "  ~VDerived() — освобождено\n";
    }
};

int main() {
    std::cout << "=== БЕЗ виртуального деструктора ===\n";
    {
        Base* p = new Derived;
        delete p;   // вызовется только ~Base! Утечка data_
    }
    std::cout << "  (data_ НЕ освобождено — утечка)\n\n";

    std::cout << "=== С виртуальным деструктором ===\n";
    {
        VBase* p = new VDerived;
        delete p;   // вызовется ~VDerived и ~VBase
    }
    std::cout << "  (всё корректно)\n";

    return 0;
}