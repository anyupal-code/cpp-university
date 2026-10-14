#include <iostream>
#include <vector>

// Алгоритмы над матрицами.

void print_matrix(const std::vector<std::vector<int>>& m) {
    for (const auto& row : m) {
        for (int x : row) std::cout << x << "\t";
        std::cout << "\n";
    }
}

int main() {
    const int n = 4;
    std::vector<std::vector<int>> m = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    std::cout << "=== Матрица ===\n";
    print_matrix(m);

    // Сумма всех элементов
    int sum = 0;
    for (const auto& row : m)
        for (int x : row)
            sum += x;
    std::cout << "\nСумма всех: " << sum << "\n";

    // Главная диагональ
    int main_diag = 0;
    for (int i = 0; i < n; ++i)
        main_diag += m[i][i];
    std::cout << "Главная диагональ: " << main_diag << "\n";

    // Побочная диагональ
    int anti_diag = 0;
    for (int i = 0; i < n; ++i)
        anti_diag += m[i][n - 1 - i];
    std::cout << "Побочная диагональ: " << anti_diag << "\n";

    // Транспонирование
    std::vector<std::vector<int>> t(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t[j][i] = m[i][j];

    std::cout << "\n=== Транспонированная ===\n";
    print_matrix(t);

    // Максимум в каждой строке
    std::cout << "\nМаксимумы по строкам: ";
    for (int i = 0; i < n; ++i) {
        int mx = m[i][0];
        for (int j = 1; j < n; ++j)
            if (m[i][j] > mx) mx = m[i][j];
        std::cout << mx << " ";
    }
    std::cout << "\n";

    // Обход по спирали (краткий пример)
    std::cout << "\nСпираль (по периметру): ";
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) std::cout << m[top][j] << " ";
        ++top;
        for (int i = top; i <= bottom; ++i) std::cout << m[i][right] << " ";
        --right;
        if (top <= bottom) {
            for (int j = right; j >= left; --j) std::cout << m[bottom][j] << " ";
            --bottom;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i) std::cout << m[i][left] << " ";
            ++left;
        }
    }
    std::cout << "\n";

    return 0;
}
