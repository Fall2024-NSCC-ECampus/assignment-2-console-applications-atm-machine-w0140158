#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <stdexcept>

class Account {
public:
    Account();
    Account(const std::string& userId, const std::string& password);

    std::string getUserId() const;
    std::string getPassword() const;
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