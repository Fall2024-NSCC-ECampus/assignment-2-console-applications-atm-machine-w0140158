#include "ATM.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

ATM::ATM() : currentAccount(nullptr) {
    try {
        loadAccountsFromFile();
    } catch (const std::exception& e) {
        std::cerr << "Error loading accounts: " << e.what() << std::endl;
    }
}

void ATM::start() {
    char option;

    do {
        try {
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
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
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

            try {
                if (action == 'd') {
                    float amount;
                    std::cout << "Deposit amount: ";
                    std::cin >> amount;
                    currentAccount->deposit(amount);
                    saveAccountsToFile(); // Save after deposit
                    std::cout << "New balance: $" << currentAccount->getBalance() << std::endl;
                } else if (action == 'w') {
                    float amount;
                    std::cout << "Withdraw amount: ";
                    std::cin >> amount;
                    if (currentAccount->withdraw(amount)) {
                        saveAccountsToFile(); // Save after withdrawal
                        std::cout << "New balance: $" << currentAccount->getBalance() << std::endl;
                    } else {
                        std::cout << "Insufficient funds!" << std::endl;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (action != 'q');

        currentAccount = nullptr;
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
        accounts.emplace_back(userId, password);
        try {
            saveAccountsToFile();
            std::cout << "Account created!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving account: " << e.what() << std::endl;
        }
    }
}

Account* ATM::findAccount(const std::string& userId) {
    for (auto& account : accounts) {
        if (account.getUserId() == userId) {
            return &account;
        }
    }
    return nullptr;
}

// Save accounts to a text file
void ATM::saveAccountsToFile() {
    std::ofstream outFile("accounts.txt", std::ios::trunc);
    if (!outFile) {
        throw std::ios_base::failure("Error opening accounts.txt for writing.");
    }

    for (const auto& account : accounts) {
        outFile << account.getUserId() << " "
                << account.getBalance() << "\n";
    }

    if (!outFile) {
        throw std::ios_base::failure("Error occurred while writing to accounts.txt.");
    }

    std::cout << "Accounts saved to file successfully." << std::endl;
}

// Load accounts from a text file
void ATM::loadAccountsFromFile() {
    std::ifstream inFile("accounts.txt");
    if (!inFile) {
        throw std::ios_base::failure("Error opening accounts.txt for reading.");
    }

    std::string userId;
    float balance;

    while (inFile >> userId >> balance) {
        Account account(userId, "");
        account.deposit(balance);
        accounts.push_back(account);
    }

    if (!inFile.eof() && inFile.fail()) {
        throw std::ios_base::failure("Error occurred while reading from accounts.txt.");
    }

    std::cout << "Accounts loaded from file successfully." << std::endl;
}
