#include "ATM.h"
#include <iostream>
#include <fstream>

ATM::ATM() : currentAccount(nullptr) {
    loadAccountsFromFile(); // Load accounts when ATM starts
}

void ATM::start() {
    char option;

    do {
        printMenu();
        std::cin >> option;

        switch (option) {
            case 'l':
                login();
                break;
            case 'c':
                createAccount();
                break;
            case 'q':
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Try again." << std::endl;
        }
    } while (option != 'q');
}

void ATM::printMenu() {
    std::cout << "ATM Menu:\n"
              << "l - Login\n"
              << "c - Create Account\n"
              << "q - Quit\n"
              << "> ";
}

void ATM::login() {
    std::string userId, password;
    std::cout << "Enter user ID: ";
    std::cin >> userId;
    std::cout << "Enter password: ";
    std::cin >> password;

    Account* account = findAccount(userId);
    if (account && account->isValid(userId, password)) {
        currentAccount = account;
        std::cout << "Login successful! Balance: $" << currentAccount->getBalance() << std::endl;

        // Simple operations after login
        char action;
        do {
            std::cout << "d - Deposit, w - Withdraw, q - Logout\n> ";
            std::cin >> action;

            if (action == 'd') {
                float amount;
                std::cout << "Deposit amount: ";
                std::cin >> amount;
                currentAccount->deposit(amount);
                std::cout << "New balance: $" << currentAccount->getBalance() << std::endl;
            } else if (action == 'w') {
                float amount;
                std::cout << "Withdraw amount: ";
                std::cin >> amount;
                if (currentAccount->withdraw(amount)) {
                    std::cout << "New balance: $" << currentAccount->getBalance() << std::endl;
                } else {
                    std::cout << "Insufficient funds!" << std::endl;
                }
            }
        } while (action != 'q');

        currentAccount = nullptr; // Logout
    } else {
        std::cout << "Invalid login." << std::endl;
    }
}

void ATM::createAccount() {
    std::string userId, password;
    std::cout << "Enter new user ID: ";
    std::cin >> userId;
    std::cout << "Enter new password: ";
    std::cin >> password;

    if (findAccount(userId) != nullptr) {
        std::cout << "Account already exists!" << std::endl;
    } else {
        accounts.emplace_back(userId, password); // Create a new account
        saveAccountsToFile(); // Save accounts to file
        std::cout << "Account created!" << std::endl;
    }
}

Account* ATM::findAccount(const std::string& userId) {
    for (auto& account : accounts) {
        if (account.getUserId() == userId) {
            return &account; // Return a pointer to the found account
        }
    }
    return nullptr; // Account not found
}

// Save accounts to a text file
void ATM::saveAccountsToFile() {
    std::ofstream outFile("accounts.txt", std::ios::trunc);
    if (!outFile) {
        std::cerr << "Error opening accounts.txt for writing!" << std::endl;
        return;
    }

    for (const auto& account : accounts) {
        outFile << account.getUserId() << " "
                << account.getBalance() << "\n"; // Save user ID and balance only
    }

    std::cout << "Accounts saved to file successfully." << std::endl;
}

// Load accounts from a text file
void ATM::loadAccountsFromFile() {
    std::ifstream inFile("accounts.txt");
    if (!inFile) {
        std::cout << "No existing accounts found. A new file will be created." << std::endl;
        return;
    }

    std::string userId;
    float balance;

    while (inFile >> userId >> balance) {
        Account account(userId, "");
        account.deposit(balance);
        accounts.push_back(account);
    }

    std::cout << "Accounts loaded from file successfully." << std::endl;
}