#include <iostream>

// Указатель как параметр функции.

// Обмен двух значений
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Сумма массива
int sum(int* arr, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += arr[i];
    }
    return s;
}

// Обнулить массив
void zero(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
}

int main() {
    int a = 5, b = 10;
    std::cout << "До swap:    a = " << a << ", b = " << b << "\n";
    swap(&a, &b);
    std::cout << "После swap: a = " << a << ", b = " << b << "\n\n";

    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << "Сумма: " << sum(arr, 5) << "\n";

    zero(arr, 5);
    std::cout << "После zero: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
