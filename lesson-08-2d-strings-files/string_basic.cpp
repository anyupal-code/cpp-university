#include <iostream>
#include <string>

// Строки std::string: создание, длина, обход, конкатенация.

int main() {
    // Создание
    std::string s1 = "Hello";
    std::string s2{"World"};
    std::string s3(5, 'x');      // "xxxxx"
    std::string s4 = s1;         // копия

    std::cout << "s1 = " << s1 << "\n";
    std::cout << "s2 = " << s2 << "\n";
    std::cout << "s3 = " << s3 << "\n";
    std::cout << "s4 = " << s4 << "\n\n";

    // Длина
    std::cout << "s1.size()   = " << s1.size() << "\n";
    std::cout << "s1.length() = " << s1.length() << "\n";
    std::cout << "s1.empty()  = " << s1.empty() << "\n\n";

    // Конкатенация
    std::string greeting = s1 + ", " + s2 + "!";
    std::cout << "Конкатенация: " << greeting << "\n";

    greeting += "!!!";
    std::cout << "После +=:     " << greeting << "\n\n";

    // Доступ
    std::cout << "greeting[0]      = " << greeting[0] << "\n";
    std::cout << "greeting.at(1)   = " << greeting.at(1) << "\n";
    std::cout << "greeting.front() = " << greeting.front() << "\n";
    std::cout << "greeting.back()  = " << greeting.back() << "\n\n";

    // Обход
    std::cout << "Символы: ";
    for (char c : s1) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // Изменение
    s1[0] = 'h';
    std::cout << "После s1[0] = 'h': " << s1 << "\n";

    // Сравнение
    std::string a = "abc", b = "abd";
    std::cout << "\n\"abc\" < \"abd\"? " << (a < b) << "\n";
    std::cout << "\"abc\" == \"abc\"? " << (a == "abc") << "\n";

    return 0;
}
