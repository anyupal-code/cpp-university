#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

// unordered_map и unordered_set: хеш-таблицы.

int main() {
    std::cout << "=== unordered_map ===\n";

    std::unordered_map<std::string, int> freq;

    freq["apple"] = 3;
    freq["banana"] = 5;
    freq["cherry"] = 2;
    freq["date"] = 7;

    std::cout << "Размер: " << freq.size() << "\n\n";

    std::cout << "Обход (порядок произвольный):\n";
    for (const auto& [word, count] : freq) {
        std::cout << "  " << word << ": " << count << "\n";
    }

    std::cout << "\nПоиск:\n";
    std::cout << "contains(\"apple\")? " << freq.contains("apple") << "\n";
    std::cout << "contains(\"fig\")?   " << freq.contains("fig") << "\n\n";

    std::cout << "=== unordered_set ===\n";

    std::unordered_set<int> s = {5, 2, 8, 1, 9, 2, 5, 1};

    std::cout << "Размер: " << s.size() << " (дубликаты удалены)\n";
    std::cout << "Содержимое: ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n\n";

    s.insert(100);
    s.insert(100);
    std::cout << "После insert(100) × 2: размер = " << s.size() << "\n";

    // Проверка скорости на большом наборе
    std::cout << "\n=== Сравнение с map ===\n";
    std::map<std::string, int> m;
    std::unordered_map<std::string, int> um;

    for (int i = 0; i < 10000; ++i) {
        std::string key = "key_" + std::to_string(i);
        m[key] = i;
        um[key] = i;
    }

    std::cout << "map:           " << m.size() << " элементов\n";
    std::cout << "unordered_map: " << um.size() << " элементов\n";

    return 0;
}