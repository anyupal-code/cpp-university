#include <iostream>
#include <string>
#include <utility>
#include <vector>

// std::move в действии.

int main() {
    std::cout << "=== Строки ===\n";
    std::string a = "Hello, World!";
    std::cout << "a = \"" << a << "\", size = " << a.size() << "\n";

    std::string b = std::move(a);
    std::cout << "После b = std::move(a):\n";
    std::cout << "  b = \"" << b << "\", size = " << b.size() << "\n";
    std::cout << "  a = \"" << a << "\", size = " << a.size()
              << " (обычно пустая)\n\n";

    // После move объект в «валидном, но неопределённом» состоянии.
    // Читать можно, но обычно пусто.

    std::cout << "=== Векторы ===\n";
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = std::move(v1);

    std::cout << "v1.size() = " << v1.size() << " (перемещён)\n";
    std::cout << "v2.size() = " << v2.size() << "\n\n";

    // Move в контейнер
    std::cout << "=== push_back + move ===\n";
    std::vector<std::string> words;

    std::string word = "Pascal";
    words.push_back(std::move(word));      // без копии
    words.push_back("C++");                // временный -> move
    words.push_back(std::string("Go"));    // то же

    for (const auto& w : words) {
        std::cout << "  " << w << "\n";
    }

    // Не используйте объект после move
    // std::cout << word << "\n";   // работает, но значение неопределено

    return 0;
}
