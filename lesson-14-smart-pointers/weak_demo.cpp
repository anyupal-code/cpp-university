#include <iostream>
#include <memory>

// weak_ptr: слабая ссылка.

int main() {
    std::cout << "=== Создание ===\n";
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;

    std::cout << "sp.use_count() = " << sp.use_count() << "\n";
    std::cout << "(wp не считается — он не владелец)\n\n";

    // Проверка живости
    std::cout << "wp.expired()? " << wp.expired() << "\n\n";

    // Доступ через lock()
    std::cout << "=== lock() ===\n";
    if (auto locked = wp.lock()) {
        std::cout << "*locked = " << *locked << "\n";
        std::cout << "use_count внутри: " << locked.use_count() << "\n";
    }
    std::cout << "После выхода: use_count = " << sp.use_count() << "\n\n";

    // Сброс владельца
    std::cout << "=== sp.reset() ===\n";
    sp.reset();

    std::cout << "wp.expired()? " << wp.expired() << "\n";

    if (auto locked = wp.lock()) {
        std::cout << "*locked = " << *locked << "\n";
    } else {
        std::cout << "Объект уничтожен — lock() вернул nullptr\n";
    }

    return 0;
}
