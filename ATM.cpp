#include "ATM.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <stdlib.h>

ATM::ATM() : currentAccount(nullptr) {
    try {
        loadAccountsFromFile();
    } catch (const std::exception& e) {
        std::cerr << "Error loading accounts: " << e.what() << std::endl;
    }
}

void ATM::start() {
    std::cout << "Hi! Welcome to Mr. Zamar's ATM Machine!" << std::endl;
    char option;

    do {
        try {
            printIntroMenu();
            std::cin >> option;

            switch (option) {
                case 'l':
                    login();
                    break;
                case 'c':
                    createAccount();
                    break;
                case 'q':
                    std::cout << "Thanks for stopping by!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid option. Try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } while (option != 'q');
}

void ATM::printIntroMenu() {
    std::cout << "\nPlease select an option from the menu below:\n"
              << "l  -> Login\n"
              << "c -> Create New Account\n"
              << "q -> Quit\n"
              << "> ";
}

void ATM::printMainMenu() {
    std::cout << "\nd  -> Deposit Money\n"
              << "w -> Withdraw Money\n"
              << "r  -> Request Balance\n"
              << "q -> Quit\n"
              << "> ";
}

void ATM::login() {
    std::string userId, password;
    std::cout << "\nPlease enter your user id: ";
    std::cin >> userId;
    std::cout << "Please enter your password: ";
    std::cin >> password;

    Account* account = findAccount(userId);
    if (account && account->isValid(userId, password)) {
        currentAccount = account;
        std::cout << "\nAccess Granted!" << std::endl;

        // Main menu after successful login
        char action;
        do {
            printMainMenu();
            std::cin >> action;

            try {
                if (action == 'd') {
                    float amount;
                    std::cout << "Amount of deposit: $";
                    std::cin >> amount;
                    currentAccount->deposit(amount);
                    saveAccountsToFile(); // Save after deposit
                    std::cout << "\nNew balance: $" << currentAccount->getBalance() << std::endl;
                } else if (action == 'w') {
                    float amount;
                    std::cout << "Amount of withdrawal: $";
                    std::cin >> amount;
                    if (currentAccount->withdraw(amount)) {
                        saveAccountsToFile(); // Save after withdrawal
                        std::cout << "\nNew balance: $" << currentAccount->getBalance() << std::endl;
                    } else {
                        std::cout << "\nInsufficient funds!" << std::endl;
                    }
                } else if (action == 'r') {
                    std::cout << "\nYour balance is $" << currentAccount->getBalance() << std::endl;
                } else if (action != 'q') {
                    std::cout << "\nInvalid option. Try again." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (action != 'q');

        currentAccount = nullptr; // Logout
    } else {
        std::cout << "\n******** LOGIN FAILED! ********" << std::endl;
    }
}

void ATM::createAccount() {
    std::string userId, password;
    std::cout << "\nPlease enter your user id: ";
    std::cin >> userId;
    std::cout << "Please enter your password: ";
    std::cin >> password;

    if (findAccount(userId) != nullptr) {
        std::cout << "\nAccount already exists!" << std::endl;
    } else {
        accounts.emplace_back(userId, password);
        try {
            saveAccountsToFile();
            std::cout << "\nThank You! Your account has been created!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving account: " << e.what() << std::endl;
        }
    }

    // Debugging statement
    std::cout << "Debug: Account creation process finished." << std::endl;
}


Account* ATM::findAccount(const std::string& userId) {
    for (auto& account : accounts) {
        if (account.getUserId() == userId) {
            return &account;
        }
    }
    return nullptr;
}


void ATM::saveAccountsToFile() {
    std::ofstream outFile("accounts.txt", std::ios::trunc);

    // If unable to open the file, report an error
    if (!outFile) {
        std::cerr << "Error: Unable to create or open accounts.txt for writing." << std::endl;
        return;
    }

    for (const auto& account : accounts) {
        outFile << account.getUserId() << " "
                << account.getPassword() << " "
                << account.getBalance() << "\n";
    }

    // Confirm successful saving to the file
    if (outFile.fail()) {
        std::cerr << "Error: Failed to write data to accounts.txt." << std::endl;
    } else {
        std::cout << "\nAccounts saved to file successfully." << std::endl;
    }

    outFile.close();
}




void ATM::loadAccountsFromFile() {
    std::ifstream inFile("accounts.txt");

    // Create the file if it doesn't exist
    if (!inFile) {
        std::cerr << "No accounts file found. Creating a new empty file." << std::endl;
        std::ofstream outFile("accounts.txt");
        if (!outFile) {
            std::cerr << "Error creating accounts.txt file." << std::endl;
            return;
        }
        outFile.close();
        return;
    }

    std::string userId, password;
    float balance;

    while (true) {
        inFile >> userId >> password >> balance;

        // Check if we reached the end of the file
        if (inFile.eof()) {
            break;
        }

        // Check if reading failed
        if (inFile.fail()) {
            std::cerr << "Error reading from file. Clearing error state and skipping line." << std::endl;
            std::cerr << "Debug info - userId: " << userId << ", password: " << password << ", balance: " << balance << std::endl;
            inFile.clear(); // Clear error state
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Additional validation for balance
        if (balance < 0) {
            std::cerr << "Invalid balance for account: " << userId << ". Skipping this account." << std::endl;
            continue;
        }

        // If everything is read correctly, add the account
        Account account(userId, password);
        account.deposit(balance);
        accounts.push_back(account);
        std::cout << "Loaded account: " << userId << " with balance $" << balance << std::endl;
    }

    if (!inFile.eof() && inFile.fail()) {
        std::cerr << "Final error occurred while reading from accounts.txt." << std::endl;
    } else {
        std::cout << "\nAccounts loaded from file successfully." << std::endl;
    }
}


