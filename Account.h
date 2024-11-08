
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    Account();
    Account(const std::string& userId, const std::string& password);

    std::string getUserId() const;
    float getBalance() const;
    void deposit(float amount);
    bool withdraw(float amount);
    bool isValid(const std::string& userId, const std::string& password) const;

private:
    std::string userId;
    std::string password;
    float balance;
};

#endif // ACCOUNT_H
