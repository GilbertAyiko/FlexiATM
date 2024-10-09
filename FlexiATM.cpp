#include <iostream>
#include <unordered_map>
#include <limits>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h> // For _getch() to hide password input
#include <fstream>  // For file operations

using namespace std;

// Struct to hold account information
struct Account {
    string password;
    double balance;
    vector<string> transactionHistory; // To keep track of transactions
    string firstName;
    string lastName;
    string occupation;
    string gender;
    string accountType;
    string nationality;
    string phoneNumber;
    string emailAddress;
    string accountNumber; // Unique account number
};

// Global variable to store accounts
unordered_map<string, Account> accounts;
int accountCounter = 1000; // Starting account number

// Function prototypes
void displayIntroMenu();
void createAccount();
bool login(string &userId);
void displayMainMenu(const string &userId);
void withdrawMoney(const string &userId);
void depositMoney(const string &userId);
void requestBalance(const string &userId);
void transferMoney(const string &userId);
void changePassword(const string &userId);
void displayTransactionHistory(const string &userId);
void displayAccountInfo(const string &userId);
void printMiniStatement(const string &userId);

int main() {
    char choice;
    string userId;

    cout << "Hi! Welcome to the ATM Machine!" << endl;

    do {
        displayIntroMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 'l': {
                if (login(userId)) {
                    char mainChoice;
                    do {
                        displayMainMenu(userId);
                        cin >> mainChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

                        switch (mainChoice) {
                            case 'd':
                                depositMoney(userId);
                                break;
                            case 'w':
                                withdrawMoney(userId);
                                break;
                            case 'r':
                                requestBalance(userId);
                                break;
                            case 't':
                                transferMoney(userId);
                                break;
                            case 'p':
                                changePassword(userId);
                                break;
                            case 'h':
                                displayTransactionHistory(userId);
                                break;
                            case 'a':
                                displayAccountInfo(userId);
                                break;
                            case 'm': // Option for mini statement
                                printMiniStatement(userId);
                                break;
                            case 'q':
                                cout << "Logging out..." << endl;
                                break;
                            default:
                                cout << "Invalid option. Please try again." << endl;
                        }
                    } while (mainChoice != 'q');
                } else {
                    cout << "* LOGIN FAILED! *" << endl;
                }
                break;
            }
            case 'c':
                createAccount();
                break;
            case 'q':
                cout << "Thank you for using the ATM Machine. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }

    } while (choice != 'q');

    return 0;
}

void displayIntroMenu() {
    cout << "Please select an option from the menu below:" << endl;
    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
}

void createAccount() {
    string userId, password;

    cout << "Please enter your user id: ";
    cin >> userId;

    if (accounts.find(userId) != accounts.end()) {
        cout << "Account with this ID already exists. Please try logging in." << endl;
        return;
    }

    cout << "Please enter your password: ";
    password.clear();
    char ch;
    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { // 8 is Backspace
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Show '*' for each character
        }
    }
    cout << endl;

    // Additional fields
    string firstName, lastName, occupation, gender, accountType, nationality, phoneNumber, emailAddress;

    cout << "First Name: ";
    cin >> firstName;
    cout << "Last Name: ";
    cin >> lastName;
    cout << "Occupation: ";
    cin >> occupation;
    cout << "Gender (M/F): ";
    cin >> gender;
    cout << "Account Type: ";
    cin >> accountType;
    cout << "Nationality: ";
    cin >> nationality;
    cout << "Phone Number: ";
    cin >> phoneNumber;
    cout << "Email Address: ";
    cin >> emailAddress;

    // Create the account
    string accountNumber = "ACCT" + to_string(accountCounter++); // Generate a unique account number
    accounts[userId] = Account{password, 0.0, {}, firstName, lastName, occupation, gender, accountType, nationality, phoneNumber, emailAddress, accountNumber};
    cout << "Thank You! Your account has been created with account number: " << accountNumber << "!" << endl;
}

bool login(string &userId) {
    string password;

    cout << "Please enter your user id: ";
    cin >> userId;
    cout << "Please enter your password: ";
    password.clear();
    char ch;
    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { // 8 is Backspace
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Show '*' for each character
        }
    }
    cout << endl;

    if (accounts.find(userId) != accounts.end() && accounts[userId].password == password) {
        cout << "Access Granted!" << endl;
        return true;
    } else {
        return false;
    }
}

void displayMainMenu(const string &userId) {
    cout << "d -> Deposit Money" << endl;
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "t -> Transfer Money" << endl;
    cout << "p -> Change Password" << endl;
    cout << "h -> View Transaction History" << endl;
    cout << "a -> View Account Information" << endl;
    cout << "m -> Print Mini Statement" << endl; // Added option for mini statement
    cout << "q -> Quit" << endl;
    cout << "> ";
}

void depositMoney(const string &userId) {
    double amount;

    cout << "Amount of deposit: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please try again." << endl;
        return;
    }

    accounts[userId].balance += amount;
    accounts[userId].transactionHistory.push_back("Deposited: $" + to_string(amount));
    cout << "Deposit successful." << endl;
}

void withdrawMoney(const string &userId) {
    double amount;
    const double transactionFee = 2.0; // Fixed fee for withdrawal

    cout << "Amount of withdrawal: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please try again." << endl;
        return;
    }

    if (accounts[userId].balance >= (amount + transactionFee)) {
        accounts[userId].balance -= (amount + transactionFee);
        accounts[userId].transactionHistory.push_back("Withdrew: $" + to_string(amount) + " with fee: $" + to_string(transactionFee));
        cout << "Withdrawal successful. A fee of $" << transactionFee << " has been applied." << endl;
    } else {
        cout << "Insufficient balance. Please try again." << endl;
    }
}

void requestBalance(const string &userId) {
    cout << "Your balance is $" << fixed << setprecision(2) << accounts[userId].balance << "." << endl;
}

void transferMoney(const string &userId) {
    string targetAccountNumber, targetUserId, targetAccountName, reason;
    double amount;
    const double transactionFee = 2.0; // Fixed fee for transfer

    cout << "Enter the target account number: ";
    cin >> targetAccountNumber;

    // Find the user by account number
    bool accountFound = false;
    for (const auto& [id, account] : accounts) {
        if (account.accountNumber == targetAccountNumber) {
            targetUserId = id;
            targetAccountName = account.firstName + " " + account.lastName; // Assuming this is the account name
            accountFound = true;
            break;
        }
    }

    if (!accountFound) {
        cout << "Target account does not exist." << endl;
        return;
    }

    cout << "Target account name: " << targetAccountName << endl;
    cout << "Amount to transfer: $";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please try again." << endl;
        return;
    }

    cout << "Reason for transfer: ";
    cin.ignore(); // To clear the newline character left in the input buffer
    getline(cin, reason);

    if (accounts[userId].balance >= (amount + transactionFee)) {
        accounts[userId].balance -= (amount + transactionFee);
        accounts[targetUserId].balance += amount;
        accounts[userId].transactionHistory.push_back("Transferred: $" + to_string(amount) + " to " + targetAccountNumber + " (" + targetAccountName + ") with fee: $" + to_string(transactionFee) + ". Reason: " + reason);
        accounts[targetUserId].transactionHistory.push_back("Received: $" + to_string(amount) + " from " + userId + " (Reason: " + reason + ")");
        cout << "Transfer successful. A fee of $" << transactionFee << " has been applied." << endl;
    } else {
        cout << "Insufficient balance. Please try again." << endl;
    }
}


void changePassword(const string &userId) {
    string oldPassword, newPassword, confirmPassword;

    cout << "Enter your old password: ";
    oldPassword.clear();
    char ch;
    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { // 8 is Backspace
            if (oldPassword.length() > 0) {
                oldPassword.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            oldPassword.push_back(ch);
            cout << '*'; // Show '*' for each character
        }
    }
    cout << endl;

    if (accounts[userId].password != oldPassword) {
        cout << "Old password is incorrect." << endl;
        return;
    }

    cout << "Enter your new password: ";
    newPassword.clear();
    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { // 8 is Backspace
            if (newPassword.length() > 0) {
                newPassword.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            newPassword.push_back(ch);
            cout << '*'; // Show '*' for each character
        }
    }
    cout << endl;

    cout << "Re-enter your new password: ";
    confirmPassword.clear();
    while ((ch = _getch()) != 13) { // 13 is Enter key
        if (ch == 8) { // 8 is Backspace
            if (confirmPassword.length() > 0) {
                confirmPassword.pop_back();
                cout << "\b \b"; // Move back, print space, move back again
            }
        } else {
            confirmPassword.push_back(ch);
            cout << '*'; // Show '*' for each character
        }
    }
    cout << endl;

    if (newPassword != confirmPassword) {
        cout << "Passwords do not match. Please try again." << endl;
        return;
    }

    if (newPassword == accounts[userId].password) {
        cout << "New Password can't be the same as Old Password." << endl;
        return;
    }

    accounts[userId].password = newPassword;
    cout << "Password changed successfully." << endl;
}

void displayTransactionHistory(const string &userId) {
    cout << "Transaction History:" << endl;
    for (const string &transaction : accounts[userId].transactionHistory) {
        cout << "- " << transaction << endl;
    }
}

void printMiniStatement(const string &userId) {
    ofstream outFile(userId + "_mini_statement.txt");
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    outFile << "Mini Statement for User ID: " << userId << endl;
    outFile << "Account Number: " << accounts[userId].accountNumber << endl;
    outFile << "Current Balance: $" << fixed << setprecision(2) << accounts[userId].balance << endl;
    outFile << "Transaction History:" << endl;
    
    for (const string &transaction : accounts[userId].transactionHistory) {
        outFile << "- " << transaction << endl;
    }

    outFile.close();
    cout << "Mini statement saved as " << userId << "_mini_statement.txt" << endl;
}

void displayAccountInfo(const string &userId) {
    const Account &account = accounts[userId];
    cout << "Account Information:" << endl;
    cout << "User ID: " << userId << endl;
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Current Balance: $" << fixed << setprecision(2) << account.balance << endl;
    cout << "Name: " << account.firstName << " " << account.lastName << endl;
    cout << "Occupation: " << account.occupation << endl;
    cout << "Gender: " << account.gender << endl;
    cout << "Account Type: " << account.accountType << endl;
    cout << "Nationality: " << account.nationality << endl;
    cout << "Phone Number: " << account.phoneNumber << endl;
    cout << "Email Address: " << account.emailAddress << endl;
}
