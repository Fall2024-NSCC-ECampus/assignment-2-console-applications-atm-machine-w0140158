#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include <vector>
#include <string>

class ATM {
public:
    ATM();
    void start();

private:
    void printMenu();
    void login();
    void createAccount();
    Account* findAccount(const std::string& userId);
    void saveAccountsToFile();
    void loadAccountsFromFile();

    std::vector<Account> accounts;
    Account* currentAccount;
};

#endif // ATM_H
