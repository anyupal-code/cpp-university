#include <iostream>

// new / delete и new[] / delete[].

int main() {
    // Один объект
    int* p = new int(42);
    std::cout << "*p = " << *p << "\n";
    delete p;
    p = nullptr;

    // Массив
    int* arr = new int[5];
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }

    std::cout << "Массив: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    delete[] arr;
    arr = nullptr;

    // new без delete — утечка (не запускать в цикле!)
    // int* leak = new int(10);
    // delete leak;  // ← не забудь

    std::cout << "\nВсё освобождено\n";

    return 0;
}
