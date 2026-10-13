#include <iostream>
#include <string>

// Ввод и вывод: cin, getline, cout.

int main() {
    int age;
    std::string name;

    std::cout << "Введите возраст: ";
    std::cin >> age;

    // «Съедаем» Enter, оставшийся после cin >>
    std::cin.ignore();

    std::cout << "Введите имя: ";
    std::getline(std::cin, name);

    std::cout << "\nПривет, " << name << "!\n";
    std::cout << "Тебе " << age << " лет.\n";

    return 0;
}