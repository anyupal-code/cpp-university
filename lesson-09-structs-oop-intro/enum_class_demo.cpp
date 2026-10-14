#include <iostream>
#include <utility>

// enum class: строгая типизация, имена в области видимости enum.

enum class Color {
    Red,
    Green,
    Blue
};

enum class Status {
    Ok       = 200,
    NotFound = 404,
    Error    = 500
};

const char* color_name(Color c) {
    switch (c) {
        case Color::Red:   return "красный";
        case Color::Green: return "зелёный";
        case Color::Blue:  return "синий";
    }
    return "неизвестный";
}

int main() {
    Color c = Color::Green;
    std::cout << "c = " << color_name(c) << "\n";

    // Обращение через :: — имена не конфликтуют
    if (c == Color::Green) {
        std::cout << "Это зелёный\n";
    }

    // Преобразование в число
    std::cout << "\nstatic_cast<int>(Color::Green) = "
              << static_cast<int>(Color::Green) << "\n";

    // C++23: std::to_underlying — то же, но читается лучше
    std::cout << "std::to_underlying(Color::Green) = "
              << std::to_underlying(Color::Green) << "\n\n";

    // Status с явными значениями
    Status s = Status::NotFound;
    std::cout << "Status::NotFound = "
              << static_cast<int>(s) << "\n";

    // Нельзя сравнить с int напрямую:
    // if (s == 404) {}   // ошибка компиляции

    return 0;
}
