#include <iostream>
#include <string>

// Ссылки vs указатели.

// По ссылке
void inc_ref(int& x) {
    ++x;
}

// По указателю
void inc_ptr(int* p) {
    ++(*p);
}

// Возврат ссылки на элемент (осторожно: контейнер должен жить)
int& get_element(int arr[], int index) {
    return arr[index];
}

// Константная ссылка — без копирования, без изменения
void print(const std::string& s) {
    std::cout << s << "\n";
}

int main() {
    int a = 5;
    inc_ref(a);
    std::cout << "после inc_ref: a = " << a << "\n";

    inc_ptr(&a);
    std::cout << "после inc_ptr: a = " << a << "\n\n";

    // Ссылка как псевдоним
    int x = 10;
    int& ref = x;
    ref = 20;
    std::cout << "x = " << x << " (через ref)\n\n";

    // Возврат ссылки
    int arr[5] = {1, 2, 3, 4, 5};
    get_element(arr, 2) = 100;
    std::cout << "arr[2] = " << arr[2] << "\n\n";

    std::string s = "Hello, World!";
    print(s);

    return 0;
}
