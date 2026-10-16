#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

// Задача 6. LRU-кэш (Least Recently Used).

class LRUCache {
    std::size_t capacity_;
    std::list<std::pair<int, int>> items_;   // front = самые свежие
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index_;

public:
    explicit LRUCache(std::size_t cap) : capacity_(cap) {}

    int get(int key) {
        auto it = index_.find(key);
        if (it == index_.end()) return -1;

        // Переместить в начало (свежий)
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = index_.find(key);
        if (it != index_.end()) {
            // Обновить и переместить в начало
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }

        // Новый элемент
        if (items_.size() >= capacity_) {
            // Удалить самый старый (с конца)
            int old_key = items_.back().first;
            items_.pop_back();
            index_.erase(old_key);
        }

        items_.emplace_front(key, value);
        index_[key] = items_.begin();
    }

    void print() const {
        std::cout << "  cache: [";
        bool first = true;
        for (const auto& [k, v] : items_) {
            if (!first) std::cout << ", ";
            std::cout << k << ":" << v;
            first = false;
        }
        std::cout << "]\n";
    }

    std::size_t size() const { return items_.size(); }
};

int main() {
    LRUCache cache(3);

    std::cout << "=== Ёмкость 3 ===\n";

    std::cout << "put(1, 10)\n";
    cache.put(1, 10);
    cache.print();

    std::cout << "put(2, 20)\n";
    cache.put(2, 20);
    cache.print();

    std::cout << "put(3, 30)\n";
    cache.put(3, 30);
    cache.print();

    std::cout << "\n=== get(1) — 1 становится свежим ===\n";
    std::cout << "get(1) = " << cache.get(1) << "\n";
    cache.print();

    std::cout << "\n=== put(4, 40) — вытесняется 2 ===\n";
    cache.put(4, 40);
    cache.print();

    std::cout << "\n=== get(2) — должен вернуть -1 (вытеснен) ===\n";
    std::cout << "get(2) = " << cache.get(2) << "\n";

    std::cout << "\n=== get(3) ===\n";
    std::cout << "get(3) = " << cache.get(3) << "\n";
    cache.print();

    std::cout << "\n=== put(5, 50) — вытесняется 1 или 4 (кто старше) ===\n";
    cache.put(5, 50);
    cache.print();

    std::cout << "\n=== Обновление существующего: put(3, 999) ===\n";
    cache.put(3, 999);
    cache.print();
    std::cout << "get(3) = " << cache.get(3) << "\n";

    return 0;
}