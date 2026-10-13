#include <iostream>
#include <memory>

// std::shared_ptr — общий владелец, счётчик ссылок.

struct Resource {
    std::string name;

    Resource(const std::string& n) : name(n) {
        std::cout << "Создан " << name << "\n";
    }

    ~Resource() {
        std::cout << "Уничтожен " << name << "\n";
    }
};

int main() {
    std::cout << "=== Создание ===\n";
    std::shared_ptr<Resource> a = std::make_shared<Resource>("A");
    std::cout << "use_count: " << a.use_count() << "\n\n";

    std::cout << "=== Копирование ===\n";
    {
        std::shared_ptr<Resource> b = a;
        std::cout << "use_count: " << a.use_count() << "\n";
    }
    std::cout << "После выхода b из блока: use_count = "
              << a.use_count() << "\n\n";

    std::cout << "=== Сброс ===\n";
    a.reset();
    std::cout << "После reset: use_count = " << a.use_count() << "\n";

    std::cout << "\n=== weak_ptr ===\n";
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;

    std::cout << "sp.use_count = " << sp.use_count() << "\n";
    std::cout << "wp.expired? " << wp.expired() << "\n";

    if (auto locked = wp.lock()) {
        std::cout << "wp.lock() -> " << *locked << "\n";
    }

    sp.reset();
    std::cout << "После sp.reset(): wp.expired? " << wp.expired() << "\n";

    return 0;
}
