#include <iostream>
#include <stdexcept>
#include <string>

// Свои исключения — наследники std::runtime_error.

class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InsufficientFunds : public BankException {
public:
    explicit InsufficientFunds(const std::string& msg)
        : BankException(msg) {}
};

class InvalidAmount : public BankException {
public:
    explicit InvalidAmount(const std::string& msg)
        : BankException(msg) {}
};

class Account {
private:
    double balance_;

public:
    explicit Account(double initial) : balance_(initial) {}

    void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmount("сумма должна быть > 0");
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmount("сумма должна быть > 0");
        if (amount > balance_)
            throw InsufficientFunds("недостаточно средств");
        balance_ -= amount;
    }

    double balance() const { return balance_; }
};

int main() {
    Account acc(1000);

    try {
        acc.deposit(500);
        std::cout << "Баланс: " << acc.balance() << "\n";

        acc.withdraw(200);
        std::cout << "Баланс: " << acc.balance() << "\n";

        acc.withdraw(2000);   // ошибка
    } catch (const InsufficientFunds& e) {
        std::cout << "Недостаточно средств: " << e.what() << "\n";
    } catch (const BankException& e) {
        std::cout << "Ошибка банка: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Другая ошибка: " << e.what() << "\n";
    }

    try {
        acc.deposit(-100);
    } catch (const BankException& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }

    std::cout << "Итоговый баланс: " << acc.balance() << "\n";

    return 0;
}
