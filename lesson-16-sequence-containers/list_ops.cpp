#include <iostream>
#include <list>
#include <algorithm>

// list: вставка, удаление, sort, unique, splice.

template <typename T>
void print(const std::list<T>& l) {
    std::cout << "[";
    bool first = true;
    for (const auto& x : l) {
        if (!first) std::cout << ", ";
        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
}

int main() {
    std::list<int> l = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::cout << "Исходный: "; print(l);

    std::cout << "\n=== sort ===\n";
    l.sort();
    std::cout << "После sort: "; print(l);

    std::cout << "\n=== unique ===\n";
    l.unique();
    std::cout << "После unique: "; print(l);

    std::cout << "\n=== reverse ===\n";
    l.reverse();
    std::cout << "После reverse: "; print(l);

    std::cout << "\n=== remove ===\n";
    l.remove(3);
    std::cout << "После remove(3): "; print(l);

    std::cout << "\n=== insert через итератор ===\n";
    auto it = l.begin();
    std::advance(it, 2);
    l.insert(it, 100);
    std::cout << "После insert на позиции 2: "; print(l);

    std::cout << "\n=== splice ===\n";
    std::list<int> a = {1, 2, 3};
    std::list<int> b = {10, 20, 30};
    std::cout << "a = "; print(a);
    std::cout << "b = "; print(b);

    a.splice(a.end(), b);
    std::cout << "После a.splice(a.end(), b):\n";
    std::cout << "  a = "; print(a);
    std::cout << "  b = "; print(b);
    std::cout << "  (элементы b перемещены в a, b пуст)\n";

    return 0;
}
