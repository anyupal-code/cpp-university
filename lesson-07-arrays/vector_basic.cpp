#include <iostream>
#include <vector>

// std::vector — динамический массив.

void print(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    // Создание
    std::vector<int> v1;                          // пустой
    std::vector<int> v2 = {1, 2, 3, 4, 5};        // с инициализацией
    std::vector<int> v3(5);                       // 5 нулей
    std::vector<int> v4(5, 42);                   // 5 элементов = 42

    std::cout << "v2 = "; print(v2);
    std::cout << "v4 = "; print(v4);

    // push_back
    std::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
        v.push_back(i * 10);
    }
    std::cout << "\nПосле push_back: "; print(v);
    std::cout << "Размер: " << v.size() << "\n";
    std::cout << "Ёмкость: " << v.capacity() << "\n\n";

    // Доступ
    std::cout << "v[0] = " << v[0] << "\n";
    std::cout << "v.at(1) = " << v.at(1) << "\n";
    std::cout << "v.front() = " << v.front() << "\n";
    std::cout << "v.back() = " << v.back() << "\n\n";

    // Изменение
    v[0] = 100;
    std::cout << "После v[0] = 100: "; print(v);

    v.pop_back();
    std::cout << "После pop_back:   "; print(v);

    // Обход
    std::cout << "\nRange-based: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    // По ссылке — изменение
    for (int& x : v) x *= 2;
    std::cout << "После удвоения: "; print(v);

    // clear
    v.clear();
    std::cout << "\nПосле clear: size = " << v.size()
              << ", empty = " << v.empty() << "\n";

    return 0;
}
