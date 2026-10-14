#include <iostream>
#include <string>
#include <cctype>

// Задача 3. Палиндром.
// Игнорировать регистр, пробелы и знаки препинания.

bool is_palindrome(const std::string& s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        // пропускаем не-буквы и не-цифры
        while (left < right && !std::isalnum(static_cast<unsigned char>(s[left])))
            ++left;
        while (left < right && !std::isalnum(static_cast<unsigned char>(s[right])))
            --right;

        char a = std::tolower(static_cast<unsigned char>(s[left]));
        char b = std::tolower(static_cast<unsigned char>(s[right]));

        if (a != b) return false;

        ++left;
        --right;
    }

    return true;
}

int main() {
    std::string s;
    std::cout << "Введите строку: ";
    std::getline(std::cin, s);

    if (is_palindrome(s)) {
        std::cout << "Палиндром\n";
    } else {
        std::cout << "Не палиндром\n";
    }

    return 0;
}
