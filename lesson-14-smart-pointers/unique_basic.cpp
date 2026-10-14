#include <iostream>
#include <memory>

// unique_ptr: единственный владелец.

int main() {
    // Создание
    auto p = std::make_unique<int>(42);
    std::cout << "*p = " << *p << "\n";
    std::cout << "p? " << (p != nullptr) << "\n\n";

    // Изменение
    *p = 100;
    std::cout << "После *p = 100: " << *p << "\n\n";

    // Нельзя копировать — только перемещать
    std::cout << "=== Перемещение владения ===\n";
    auto q = std::move(p);
    std::cout << "p == nullptr? " << (p == nullptr) << "\n";
    std::cout << "q == nullptr? " << (q == nullptr) << "\n";
    std::cout << "*q = " << *q << "\n\n";

    // reset
    std::cout << "=== reset ===\n";
    q.reset();
    std::cout << "После reset: q == nullptr? " << (q == nullptr) << "\n\n";

    // reset с новым объектом
    q.reset(new int(200));
    std::cout << "После reset(new int(200)): *q = " << *q << "\n\n";

    // Массив
    std::cout << "=== Массив ===\n";
    auto arr = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i)
        arr[i] = i * i;

    std::cout << "arr = ";
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}
