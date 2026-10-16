#include <iostream>
#include <set>
#include <vector>

// set: уникальные элементы, отсортированы.

int main() {
    std::vector<int> data = {5, 2, 8, 1, 9, 2, 5, 3, 1, 7};
    std::cout << "Данные: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n\n";

    // Удаление дубликатов через set
    std::set<int> s(data.begin(), data.end());

    std::cout << "Уникальные (отсортированы): ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "Размер: " << s.size() << "\n\n";

    // Вставка
    s.insert(100);
    s.insert(100);   // не добавится
    std::cout << "После insert(100) × 2: размер = " << s.size() << "\n\n";

    // Поиск
    std::cout << "=== Поиск ===\n";
    std::cout << "contains(5)? " << s.contains(5) << "\n";
    std::cout << "contains(42)? " << s.contains(42) << "\n\n";

    // Границы
    auto it_low = s.lower_bound(5);
    auto it_up = s.upper_bound(7);
    std::cout << "lower_bound(5) = " << *it_low << "\n";
    std::cout << "upper_bound(7) = " << *it_up << "\n\n";

    // Удаление
    s.erase(5);
    std::cout << "После erase(5): ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    // Обратный обход
    std::cout << "\nОбратный обход: ";
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}