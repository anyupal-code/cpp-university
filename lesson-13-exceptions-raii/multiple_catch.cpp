#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

// Несколько catch: от частных к общим.

void process(int choice) {
    if (choice == 1) {
        throw std::invalid_argument("неверный аргумент");
    } else if (choice == 2) {
        throw std::out_of_range("вне границ");
    } else if (choice == 3) {
        throw std::runtime_error("ошибка времени выполнения");
    } else if (choice == 4) {
        throw 42;   // не std::exception
    }
    std::cout << "Всё ок\n";
}

int main() {
    for (int c = 0; c <= 5; ++c) {
        std::cout << "Выбор " << c << ": ";
        try {
            process(c);
        } catch (const std::invalid_argument& e) {
            std::cout << "invalid_argument: " << e.what() << "\n";
        } catch (const std::out_of_range& e) {
            std::cout << "out_of_range: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "неизвестное исключение\n";
        }
    }

    // Пример с vector
    std::vector<int> v = {1, 2, 3};
    try {
        std::cout << "\nv.at(10) = " << v.at(10) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }

    return 0;
}
