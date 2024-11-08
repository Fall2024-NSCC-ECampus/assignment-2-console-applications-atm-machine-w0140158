# ATM Console Application

## Overview

ATM application written in C++ that allows users to create accounts, login, deposit, and withdraw money. It follows Object-Oriented Programming (OOP) principles and implements proper error handling to ensure data consistency and reliability. The account information, including user IDs and balances, is stored in a text file (`accounts.txt`) for persistence between sessions.

## Features

- **Create Account**: Users can create a new account with a user ID and password.
- **Login**: Users can log in using their user ID and password.
- **Deposit Money**: Logged-in users can deposit money into their account.
- **Withdraw Money**: Logged-in users can withdraw money from their account, provided they have sufficient balance.
- **Persistent Storage**: Account data is saved to a text file to ensure that the data is retained across different runs of the application.
- **Error Handling**: Proper error handling is implemented for invalid inputs, file access issues, and account operations.

## How to Run

1. **Compile the Program**: Use a C++ compiler (e.g., `g++`) to compile the project files:
   ```
   g++ main.cpp ATM.cpp Account.cpp -o ATMApp
   ```

2. **Run the Executable**: Execute the compiled file:
   ```
   ./ATMApp
   ```

## File Structure

- `Account.h` / `Account.cpp`: Defines the `Account` class, which handles user accounts, including deposits, withdrawals, and balance inquiries.
- `ATM.h` / `ATM.cpp`: Defines the `ATM` class, which manages account operations, user interactions, and the main menu.
- `main.cpp`: The entry point of the application.
- `accounts.txt`: Stores account data for persistence.

## Usage

Upon running the application, users are presented with a menu with the following options:
- **Login** (`l`): Log in to an existing account.
- **Create Account** (`c`): Create a new account with a user ID and password.
- **Quit** (`q`): Exit the application.

After logging in, users can:
- **Deposit** (`d`): Add money to their account.
- **Withdraw** (`w`): Withdraw money from their account.
- **Logout** (`q`): Log out of the current session.

## Data Persistence

- Account data is saved in `accounts.txt` whenever changes are made (e.g., deposit or withdrawal).
- The program loads existing accounts from `accounts.txt` when it starts, ensuring that user data is preserved between sessions.
- Proper error handling is in place to ensure that data is saved successfully, and any issues with reading or writing to the file are reported.

## Error Handling

- **Invalid Input**: The application handles invalid input, such as negative amounts for deposits or withdrawals.
- **File Access Issues**: Errors during reading from or writing to `accounts.txt` are caught and reported to the user.
- **Insufficient Funds**: The application checks if the user has enough balance before allowing a withdrawal.

## Dependencies

- A C++ compiler (e.g., `g++`).
