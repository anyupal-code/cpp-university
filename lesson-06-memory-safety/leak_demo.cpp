#include <iostream>

// Утечка памяти. ВНИМАНИЕ: пример не выполняет утечку в цикле,
// чтобы не съесть память. Показан код, который ТАК делать нельзя.

void bad_function() {
    int* p = new int(42);
    std::cout << "  внутри bad_function: *p = " << *p << "\n";
    // забыли delete p — утечка!
}

void good_function() {
    int* p = new int(42);
    std::cout << "  внутри good_function: *p = " << *p << "\n";
    delete p;   // правильно
}

int main() {
    std::cout << "bad_function:\n";
    bad_function();
    std::cout << "  (память утекла — 4 байта)\n\n";

    std::cout << "good_function:\n";
    good_function();
    std::cout << "  (память освобождена)\n\n";

    std::cout << "Если bad_function вызвать миллион раз —\n";
    std::cout << "утечёт ~4 МБ памяти.\n";

    return 0;
}