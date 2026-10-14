#include <iostream>
#include <fstream>
#include <vector>

// Задача 1. Спираль.
// Заполнить матрицу N x N единицами по спирали.
// N — нечётное, 1 <= N <= 50.

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // верхняя строка слева направо
        for (int j = left; j <= right; ++j)
            a[top][j] = 1;
        ++top;

        // правый столбец сверху вниз
        for (int i = top; i <= bottom; ++i)
            a[i][right] = 1;
        --right;

        // нижняя строка справа налево
        if (top <= bottom) {
            for (int j = right; j >= left; --j)
                a[bottom][j] = 1;
            --bottom;
        }

        // левый столбец снизу вверх
        if (left <= right) {
            for (int i = bottom; i >= top; --i)
                a[i][left] = 1;
            ++left;
        }
    }

    // Вывод
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            fout << a[i][j];
        fout << '\n';
    }

    return 0;
}
