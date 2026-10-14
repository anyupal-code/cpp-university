#include <iostream>
#include <deque>

// deque: push_front, pop_front, доступ по индексу.

void print(const std::deque<int>& d) {
    std::cout << "[";
    for (std::size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i];
        if (i + 1 < d.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    std::deque<int> d;

    std::cout << "=== push_back / push_front ===\n";
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);
    std::cout << "После push_back:  "; print(d);

    d.push_front(10);
    d.push_front(5);
    std::cout << "После push_front: "; print(d);

    std::cout << "\n=== Доступ ===\n";
    std::cout << "d[0] = " << d[0] << "\n";
    std::cout << "d[2] = " << d[2] << "\n";
    std::cout << "front = " << d.front() << "\n";
    std::cout << "back  = " << d.back() << "\n";

    std::cout << "\n=== pop_front / pop_back ===\n";
    d.pop_front();
    std::cout << "После pop_front: "; print(d);

    d.pop_back();
    std::cout << "После pop_back:  "; print(d);

    std::cout << "\n=== Очередь через deque ===\n";
    std::deque<std::string> q;
    q.push_back("задача 1");
    q.push_back("задача 2");
    q.push_back("задача 3");

    while (!q.empty()) {
        std::cout << "  Обработка: " << q.front() << "\n";
        q.pop_front();
    }

    return 0;
}
