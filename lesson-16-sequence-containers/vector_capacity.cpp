#include <iostream>
#include <vector>

// size vs capacity, рост, reserve.

int main() {
    std::cout << "=== Рост capacity ===\n";
    std::vector<int> v;

    std::cout << "Начало: size = " << v.size()
              << ", capacity = " << v.capacity() << "\n";

    for (int i = 1; i <= 20; ++i) {
        v.push_back(i);
        std::cout << "push_back(" << i << "): size = " << v.size()
                  << ", capacity = " << v.capacity() << "\n";
    }

    std::cout << "\n=== reserve ===\n";
    std::vector<int> w;
    w.reserve(100);
    std::cout << "После reserve(100): size = " << w.size()
              << ", capacity = " << w.capacity() << "\n";

    for (int i = 0; i < 50; ++i) w.push_back(i);
    std::cout << "После 50 push_back: size = " << w.size()
              << ", capacity = " << w.capacity() << " (не менялась)\n";

    std::cout << "\n=== shrink_to_fit ===\n";
    std::vector<int> u;
    u.reserve(1000);
    u.push_back(1);
    u.push_back(2);
    u.push_back(3);

    std::cout << "До shrink: size = " << u.size()
              << ", capacity = " << u.capacity() << "\n";
    u.shrink_to_fit();
    std::cout << "После:     size = " << u.size()
              << ", capacity = " << u.capacity() << "\n";

    return 0;
}
