#include <iostream>

// Ханойская башня: классическая задача на рекурсию.

int moves = 0;

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        std::cout << "Переместить диск 1 с " << from << " на " << to << "\n";
        ++moves;
        return;
    }
    hanoi(n - 1, from, aux, to);
    std::cout << "Переместить диск " << n << " с " << from << " на " << to << "\n";
    ++moves;
    hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    std::cout << "Число дисков: ";
    std::cin >> n;

    hanoi(n, 'A', 'C', 'B');

    std::cout << "\nВсего перемещений: " << moves << "\n";
    std::cout << "(минимум для n=" << n << ": " << ((1 << n) - 1) << ")\n";

    return 0;
}
