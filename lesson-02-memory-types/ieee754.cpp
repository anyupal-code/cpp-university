#include <iostream>
#include <cmath>
#include <limits>

// IEEE 754: неточность вещественных, NaN, бесконечности.

int main() {
    // 1. Не все числа представимы точно
    double a = 0.1 + 0.2;
    std::cout << "0.1 + 0.2 = " << a << "\n";
    std::cout << "0.3       = " << 0.3 << "\n";
    std::cout << "(0.1 + 0.2 == 0.3)? " << (a == 0.3) << "\n";
    std::cout << "---\n";

    // 2. Правильное сравнение с точностью
    auto nearly_equal = [](double x, double y, double eps = 1e-9) {
        return std::fabs(x - y) < eps;
    };
    std::cout << "nearly_equal(0.1+0.2, 0.3)? "
              << nearly_equal(0.1 + 0.2, 0.3) << "\n";
    std::cout << "---\n";

    // 3. Точность float vs double
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;
    std::cout.precision(15);
    std::cout << "float:  " << f << "\n";
    std::cout << "double: " << d << "\n";
    std::cout << "---\n";

    // 4. NaN и бесконечность
    double zero = 0.0;
    double inf = 1.0 / zero;
    double nan = zero / zero;
    std::cout << "1.0 / 0.0 = " << inf << "\n";
    std::cout << "0.0 / 0.0 = " << nan << "\n";
    std::cout << "isinf(inf)? " << std::isinf(inf) << "\n";
    std::cout << "isnan(nan)? " << std::isnan(nan) << "\n";
    std::cout << "nan == nan? " << (nan == nan) << "  (всегда ложь!)\n";

    return 0;
}
