#include <iostream>
#include <vector>

// Задача 2. Банкомат.
// Выдать сумму S минимальным числом купюр.
// Номиналы: 5000, 2000, 1000, 500, 200, 100.

int main() {
    const std::vector<int> notes = {5000, 2000, 1000, 500, 200, 100};

    int s;
    std::cout << "Введите сумму: ";
    std::cin >> s;

    if (s <= 0 || s % 100 != 0) {
        std::cout << "Невозможно выдать (сумма должна быть кратна 100)\n";
        return 0;
    }

    std::cout << "Выдача:\n";
    int total = 0;

    for (int n : notes) {
        int count = s / n;
        if (count > 0) {
            std::cout << "  " << n << " x " << count
                      << " = " << n * count << "\n";
            s -= n * count;
            total += count;
        }
    }

    std::cout << "Всего купюр: " << total << "\n";

    return 0;
}
