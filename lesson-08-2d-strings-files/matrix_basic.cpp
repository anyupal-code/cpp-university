#include <iostream>
#include <vector>

// Двумерные массивы: объявление, ввод, вывод.

int main() {
    // Статическая матрица 3x4
    int m[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    std::cout << "=== Статическая матрица 3x4 ===\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << "\n";
    }

    std::cout << "\nsizeof(m)         = " << sizeof(m) << " байт\n";
    std::cout << "sizeof(m[0])      = " << sizeof(m[0]) << " байт\n";
    std::cout << "sizeof(m[0][0])   = " << sizeof(m[0][0]) << " байт\n";
    std::cout << "Строк: " << sizeof(m) / sizeof(m[0]) << "\n";
    std::cout << "Столбцов: " << sizeof(m[0]) / sizeof(m[0][0]) << "\n\n";

    // Динамическая матрица: vector<vector<int>>
    int n, cols;
    std::cout << "Введите число строк и столбцов: ";
    std::cin >> n >> cols;

    std::vector<std::vector<int>> mat(n, std::vector<int>(cols));

    std::cout << "Введите " << n * cols << " чисел:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < cols; ++j)
            std::cin >> mat[i][j];

    std::cout << "\nВведённая матрица:\n";
    for (const auto& row : mat) {
        for (int x : row) {
            std::cout << x << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
