#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    Account();
    Account(const std::string& userId, const std::string& password);
    Account(const std::string & string, const std::string & password, float balance);

    std::string getUserId() const;
    float getBalance() const;
    void deposit(float amount);
    bool withdraw(float amount);
    bool isValid(const std::string& userId, const std::string& password) const; /
    void getPassword() const;

private:
    std::string userId;
    std::string password;
    float balance;
};

#endif // ACCOUNT_H
