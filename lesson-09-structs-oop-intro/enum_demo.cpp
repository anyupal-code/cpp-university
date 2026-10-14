#include <iostream>

// Обычный enum: значения попадают в общую область видимости.

enum Color {
    RED,
    GREEN,
    BLUE
};

enum Weekday {
    MON = 1,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
};

const char* color_name(Color c) {
    switch (c) {
        case RED:   return "красный";
        case GREEN: return "зелёный";
        case BLUE:  return "синий";
    }
    return "неизвестный";
}

int main() {
    Color c = GREEN;
    std::cout << "c = " << c << " (" << color_name(c) << ")\n";
    std::cout << "RED = " << RED << ", GREEN = " << GREEN << ", BLUE = " << BLUE << "\n\n";

    Weekday d = WED;
    std::cout << "WED = " << d << "\n";

    // Перебор через int
    std::cout << "\nВсе дни недели:\n";
    for (int i = MON; i <= SUN; ++i) {
        std::cout << "  день " << i << "\n";
    }

    return 0;
}
