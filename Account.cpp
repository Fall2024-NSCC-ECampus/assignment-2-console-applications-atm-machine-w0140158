#include "Account.h"


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
    balance += amount;
}


bool Account::withdraw(float amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}


bool Account::isValid(const std::string& userId, const std::string& password) const {
    return this->userId == userId && this->password == password;
}
