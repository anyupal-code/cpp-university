#include <iostream>

// Уровни доступа: private, protected, public.

class Base {
private:
    int priv_ = 1;
protected:
    int prot_ = 2;
public:
    int pub_ = 3;

    int get_priv() const { return priv_; }
};

class Derived : public Base {
public:
    void test() {
        // priv_ = 10;      // ошибка: private недоступно
        prot_ = 20;         // ок: protected
        pub_ = 30;          // ок: public
        std::cout << "  Из наследника:\n";
        std::cout << "    prot_ = " << prot_ << "\n";
        std::cout << "    pub_  = " << pub_ << "\n";
        std::cout << "    priv_ через getter = " << get_priv() << "\n";
    }
};

int main() {
    Base b;
    // b.priv_ = 1;      // ошибка: private
    // b.prot_ = 2;      // ошибка: protected снаружи
    b.pub_ = 100;        // ок

    std::cout << "=== Извне ===\n";
    std::cout << "  pub_ = " << b.pub_ << "\n";
    std::cout << "  priv_ через getter = " << b.get_priv() << "\n\n";

    std::cout << "=== Из наследника ===\n";
    Derived d;
    d.test();
    d.pub_ = 200;        // унаследованный public

    return 0;
}