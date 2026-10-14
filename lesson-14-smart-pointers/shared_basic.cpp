#include <iostream>
#include <memory>

// shared_ptr: общий владелец, счётчик ссылок.

int main() {
    // Создание
    auto a = std::make_shared<int>(42);
    std::cout << "*a = " << *a << "\n";
    std::cout << "a.use_count() = " << a.use_count() << "\n\n";

    // Копирование — увеличивает счётчик
    std::cout << "=== Копирование ===\n";
    {
        auto b = a;
        std::cout << "После auto b = a:\n";
        std::cout << "  a.use_count() = " << a.use_count() << "\n";

        auto c = b;
        std::cout << "После auto c = b:\n";
        std::cout << "  a.use_count() = " << a.use_count() << "\n";
    }
    std::cout << "После выхода b и c из блока:\n";
    std::cout << "  a.use_count() = " << a.use_count() << "\n\n";

    // reset
    std::cout << "=== reset ===\n";
    auto d = a;
    std::cout << "С d: use_count = " << a.use_count() << "\n";

    d.reset();
    std::cout << "После d.reset(): use_count = " << a.use_count() << "\n\n";

    a.reset();
    std::cout << "После a.reset(): use_count = " << a.use_count() << "\n";

    return 0;
}
