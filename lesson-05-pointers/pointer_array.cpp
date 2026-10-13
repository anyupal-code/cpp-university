#include <iostream>

// Имя массива — указатель на первый элемент.

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // Три способа обратиться к элементам
    std::cout << "arr[2]       = " << arr[2] << "\n";
    std::cout << "*(arr + 2)   = " << *(arr + 2) << "\n";

    int* p = arr;
    std::cout << "p[2]         = " << p[2] << "\n";
    std::cout << "*(p + 2)     = " << *(p + 2) << "\n";

    // Адреса
    std::cout << "\narr   = " << arr << " (адрес arr[0])\n";
    std::cout << "&arr[0] = " << &arr[0] << "\n";
    std::cout << "p     = " << p << "\n";

    // Разница sizeof
    std::cout << "\nsizeof(arr) = " << sizeof(arr) << " (весь массив)\n";
    std::cout << "sizeof(p)   = " << sizeof(p) << " (только указатель)\n";

    // Обход через указатель
    std::cout << "\nОбход через указатель: ";
    for (int* q = arr; q < arr + 5; ++q) {
        std::cout << *q << " ";
    }
    std::cout << "\n";

    return 0;
}
