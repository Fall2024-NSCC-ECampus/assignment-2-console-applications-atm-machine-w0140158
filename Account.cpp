#include "Account.h"
#include <stdexcept>

Account::Account() : userId(""), password(""), balance(0.0f) {}

Account::Account(const std::string& userId, const std::string& password)
    : userId(userId), password(password), balance(0.0f) {}

std::string Account::getUserId() const {
    return userId;
}

float Account::getBalance() const {
    return balance;
}

void Account::deposit(float amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount cannot be negative.");
    }
    balance += amount;
}

bool Account::withdraw(float amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdrawal amount cannot be negative.");
    }
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

bool Account::isValid(const std::string& userId, const std::string& password) const {
    return this->userId == userId && this->password == password;
}