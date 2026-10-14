#include <iostream>
#include <string>
#include <cctype>

// Операции над строками: find, substr, replace, contains (C++23).

int main() {
    std::string s = "Hello, World!";

    std::cout << "Исходная: " << s << "\n\n";

    // Поиск
    std::size_t pos = s.find("World");
    if (pos != std::string::npos) {
        std::cout << "\"World\" найдено на позиции " << pos << "\n";
    }

    // contains (C++23)
    if (s.contains("Hello")) {
        std::cout << "Содержит \"Hello\"\n";
    }
    std::cout << "\n";

    // Подстрока
    std::cout << "substr(0, 5)   = " << s.substr(0, 5) << "\n";
    std::cout << "substr(7)      = " << s.substr(7) << "\n\n";

    // Замена
    std::string t = s;
    t.replace(0, 5, "Hi");
    std::cout << "После replace: " << t << "\n";

    // Вставка
    t = s;
    t.insert(5, " there");
    std::cout << "После insert:  " << t << "\n";

    // Удаление
    t = s;
    t.erase(5, 7);
    std::cout << "После erase:   " << t << "\n\n";

    // Регистр
    t = s;
    for (char& c : t) c = std::toupper(static_cast<unsigned char>(c));
    std::cout << "Верхний регистр: " << t << "\n";

    for (char& c : t) c = std::tolower(static_cast<unsigned char>(c));
    std::cout << "Нижний регистр:  " << t << "\n\n";

    // Разворот
    t = s;
    std::reverse(t.begin(), t.end());
    std::cout << "Реверс: " << t << "\n\n";

    // Числа в строки и обратно
    std::string num = std::to_string(42);
    std::cout << "to_string(42) = \"" << num << "\"\n";

    int x = std::stoi("123");
    double d = std::stod("3.14");
    std::cout << "stoi(\"123\")  = " << x << "\n";
    std::cout << "stod(\"3.14\") = " << d << "\n";

    return 0;
}
