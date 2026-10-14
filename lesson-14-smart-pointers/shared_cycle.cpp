#include <iostream>
#include <memory>

// Циклические ссылки и их решение через weak_ptr.

// ОПАСНЫЙ класс: циклическая ссылка через shared_ptr
struct BadNode {
    std::string name;
    std::shared_ptr<BadNode> next;

    explicit BadNode(const std::string& n) : name(n) {
        std::cout << "  BadNode \"" << name << "\" создан\n";
    }

    ~BadNode() {
        std::cout << "  BadNode \"" << name << "\" уничтожен\n";
    }
};

// БЕЗОПАСНЫЙ класс: одна ссылка — weak_ptr
struct GoodNode {
    std::string name;
    std::shared_ptr<GoodNode> next;
    std::weak_ptr<GoodNode> prev;    // ← слабая

    explicit GoodNode(const std::string& n) : name(n) {
        std::cout << "  GoodNode \"" << name << "\" создан\n";
    }

    ~GoodNode() {
        std::cout << "  GoodNode \"" << name << "\" уничтожен\n";
    }
};

int main() {
    std::cout << "=== ОПАСНО: цикл из shared_ptr ===\n";
    {
        auto a = std::make_shared<BadNode>("A");
        auto b = std::make_shared<BadNode>("B");

        a->next = b;
        b->next = a;   // ← цикл

        std::cout << "  a.use_count = " << a.use_count() << "\n";
        std::cout << "  b.use_count = " << b.use_count() << "\n";
    }
    // Внимание: деструкторы НЕ вызываются — утечка.
    // Программа всё равно завершится, но это утечка памяти.

    std::cout << "(объекты BadNode не уничтожены — утечка)\n\n";

    std::cout << "=== БЕЗОПАСНО: цикл разорван weak_ptr ===\n";
    {
        auto a = std::make_shared<GoodNode>("A");
        auto b = std::make_shared<GoodNode>("B");

        a->next = b;
        b->prev = a;   // ← weak_ptr, не увеличивает счётчик

        std::cout << "  a.use_count = " << a.use_count() << "\n";
        std::cout << "  b.use_count = " << b.use_count() << "\n";
    }
    // Деструкторы вызываются корректно.

    std::cout << "\nГотово\n";

    return 0;
}
