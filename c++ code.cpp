#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Account {
    int accountNumber;
    string name;
    string fatherName;
    string password;
    string phoneNumber;
    double balance;
    bool isActive;
};

void displayWelcomePage();
void registerAccount(Account* accounts, int& count);
void searchAccount(Account* accounts, int count);
void updateAccount(Account* accounts, int count);
void deleteAccount(Account* accounts, int& count);
void displayAllAccounts(Account* accounts, int count);
void depositAmount(Account* accounts, int count);
void withdrawAmount(Account* accounts, int count);
void transferAmount(Account* accounts, int count);
void saveToFile(Account* accounts, int count);
void loadFromFile(Account* accounts, int& count);
bool verifyPassword(Account* accounts, int count, int accNum, const string& password);

const int MAX_ACCOUNTS = 100;

int main() {
    Account accounts[MAX_ACCOUNTS];
    int count = 0;
    int choice;

    loadFromFile(accounts, count);
    displayWelcomePage();

    do {
        cout << "\n-------------------------------------------------\n";
        cout << "  Total Active Accounts: " << count << "          \n";
        cout << "----------------------------------------------------\n";
        cout << "  Bank Operations:                                    \n";
        cout << "  1. Register New Account                             \n";
        cout << "  2. Update Account                                  \n";
        cout << "  3. Delete Account                                  \n";
        cout << "  4. Search Account                                  \n";
        cout << "  5. Display All Accounts                             \n";
        cout << "  6. Deposit Amount                                  \n";
        cout << "  7. Withdraw Amount                                 \n";
        cout << "  8. Transfer Amount                                 \n";
        cout << "  9. Exit                                            \n";
        cout << "----------------------------------------------------\n";
        cout << "  Enter your choice (1-9): ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerAccount(accounts, count);
                break;
            case 2:
                updateAccount(accounts, count);
                break;
            case 3:
                deleteAccount(accounts, count);
                break;
            case 4:
                searchAccount(accounts, count);
                break;
            case 5:
                displayAllAccounts(accounts, count);
                break;
            case 6:
                depositAmount(accounts, count);
                break;
            case 7:
                withdrawAmount(accounts, count);
                break;
            case 8:
                transferAmount(accounts, count);
                break;
            case 9:
                saveToFile(accounts, count);
                cout << "Thanks for using our project \n";
                break;
            default:
                cout << "Invalid choice! Please select a valid option (1-9).\n";
        }
    } while (choice != 9);

    return 0;
}

void displayWelcomePage() {
    cout << "\n====================================================\n";
    cout << "      WELCOME TO Group 3 Bank Account Management System      \n";
    cout << "====================================================\n";
    cout << "        \n";
    cout << "  Established: April 1, 2025                              \n";
    cout << "----------------------------------------------------\n";
    cout << "  Press Enter to continue to the main menu...           \n";
    cin.get();
}

void registerAccount(Account* accounts, int& count) {
    if (count >= MAX_ACCOUNTS) {
        cout << "Cannot register more accounts. Limit reached!\n";
        return;
    }

    Account* newAccount = &accounts[count];
    newAccount->accountNumber = 1000 + count + 1;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, newAccount->name);
    cout << "Enter father's name: ";
    getline(cin, newAccount->fatherName);
    cout << "Enter password: ";
    getline(cin, newAccount->password);
    cout << "Enter phone number: ";
    getline(cin, newAccount->phoneNumber);
    cout << "Enter initial balance: ";
    cin >> newAccount->balance;
    newAccount->isActive = true;
    count++;
    cout << "Account registered successfully! Account Number: " << newAccount->accountNumber << endl;
}

void searchAccount(Account* accounts, int count) {
    int accNum;
    cout << "Enter account number to search: ";
    cin >> accNum;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive) {
            cout << "Account Found!\n";
            cout << "Name: " << accounts[i].name
                 << "\nFather's Name: " << accounts[i].fatherName
                 << "\nPhone Number: " << accounts[i].phoneNumber
                 << "\nBalance: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found or inactive!\n";
}

void updateAccount(Account* accounts, int count) {
    int accNum;
    cout << "Enter account number to update: ";
    cin >> accNum;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive) {
            cout << "Current Name: " << accounts[i].name << "\nEnter new name: ";
            cin.ignore();
            getline(cin, accounts[i].name);
            cout << "Current Father's Name: " << accounts[i].fatherName << "\nEnter new father's name: ";
            getline(cin, accounts[i].fatherName);
            cout << "Current Password: " << accounts[i].password << "\nEnter new password: ";
            getline(cin, accounts[i].password);
            cout << "Current Phone Number: " << accounts[i].phoneNumber << "\nEnter new phone number: ";
            getline(cin, accounts[i].phoneNumber);
            cout << "Current Balance: " << accounts[i].balance << "\nEnter new balance: ";
            cin >> accounts[i].balance;
            cout << "Account updated successfully!\n";
            return;
        }
    }
    cout << "Account not found or inactive!\n";
}

void deleteAccount(Account* accounts, int& count) {
    int accNum;
    cout << "Enter account number to delete: ";
    cin >> accNum;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive) {
            accounts[i].isActive = false;
            cout << "Account deleted successfully!\n";
            return;
        }
    }
    cout << "Account not found or already inactive!\n";
}

void displayAllAccounts(Account* accounts, int count) {
    if (count == 0) {
        cout << "No accounts available!\n";
        return;
    }

    cout << "\nAll Active Accounts:\n";
    for (int i = 0; i < count; i++) {
        if (accounts[i].isActive) {
            cout << "Account Number: " << accounts[i].accountNumber
                 << ", Name: " << accounts[i].name
                 << ", Father's Name: " << accounts[i].fatherName
                 << ", Phone Number: " << accounts[i].phoneNumber
                 << ", Balance: " << accounts[i].balance << endl;
        }
    }
}

void depositAmount(Account* accounts, int count) {
    int accNum;
    double amount;
    string password;

    cout << "Enter account number for deposit: ";
    cin >> accNum;
    cout << "Enter Password :";
    cin.ignore();
    getline(cin, password);

    if (!verifyPassword(accounts, count, accNum, password)) {
        cout << "Incorrect Password.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive) {
            cout << "Enter deposit amount: ";
            cin >> amount;
            if (amount > 0) {
                accounts[i].balance += amount;
                cout << "Deposit successful. New balance: " << accounts[i].balance << endl;
            } else {
                cout << "Invalid amount. Deposit must be positive." << endl;
            }
            return;
        }
    }
    cout << "Account not found or inactive." << endl;
}

void withdrawAmount(Account* accounts, int count) {
    int accNum;
    double amount;
    string password;

    cout << "Enter account number for withdrawal: ";
    cin >> accNum;
    cout << "Enter Password :";
    cin.ignore();
    getline(cin, password);

    if (!verifyPassword(accounts, count, accNum, password)) {
        cout << "Incorrect Password.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive) {
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount. Withdrawal must be positive." << endl;
            } else if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                cout << "Withdrawal successful. New balance: " << accounts[i].balance << endl;
            } else {
                cout << "Insufficient balance." << endl;
            }
            return;
        }
    }
    cout << "Account not found or inactive." << endl;
}

void transferAmount(Account* accounts, int count) {
    int srcAcc, destAcc;
    double amount;
    string password;

    cout << "Enter Sender account number: ";
    cin >> srcAcc;

    cout << "Enter Sender Password :";
    cin.ignore();
    getline(cin, password);

    if (!verifyPassword(accounts, count, srcAcc, password)) {
        cout << "Incorrect Password.\n";
        return;
    }

    cout << "Enter Receiver account number: ";
    cin >> destAcc;

    if (srcAcc == destAcc) {
        cout << "Error: Cannot transfer to the same account." << endl;
        return;
    }

    Account *src = nullptr, *dest = nullptr;

    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == srcAcc && accounts[i].isActive) {
            src = &accounts[i];
        }
        if (accounts[i].accountNumber == destAcc && accounts[i].isActive) {
            dest = &accounts[i];
        }
    }

    if (!src || !dest) {
        cout << "One or both accounts not found or inactive." << endl;
        return;
    }

    cout << "Enter transfer amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Transfer must be positive." << endl;
    } else if (src->balance >= amount) {
        src->balance -= amount;
        dest->balance += amount;
        cout << "Transfer successful." << endl;
        cout << "Sender new balance: " << src->balance << endl;
        cout << "Receiver new balance: " << dest->balance << endl;
    } else {
        cout << "Insufficient balance in source account." << endl;
    }
}

void saveToFile(Account* accounts, int count) {
    ofstream outFile("bank_data.txt");
    if (!outFile) {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (accounts[i].isActive) {
            outFile << accounts[i].accountNumber << " "
                    << accounts[i].name << " "
                    << accounts[i].fatherName << " "
                    << accounts[i].password << " "
                    << accounts[i].phoneNumber << " "
                    << accounts[i].balance << endl;
        }
    }
    outFile.close();
}

void loadFromFile(Account* accounts, int& count) {
    ifstream inFile("bank_data.txt");
    if (!inFile) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    count = 0;
    while (inFile >> accounts[count].accountNumber) {
        inFile.ignore();
        getline(inFile, accounts[count].name, ' ');
        getline(inFile, accounts[count].fatherName, ' ');
        getline(inFile, accounts[count].password, ' ');
        getline(inFile, accounts[count].phoneNumber, ' ');
        inFile >> accounts[count].balance;
        accounts[count].isActive = true;
        count++;
        if (count >= MAX_ACCOUNTS) break;
    }
    inFile.close();
    cout << "Loaded " << count << " accounts from file.\n";
}

bool verifyPassword(Account* accounts, int count, int accNum, const string& password) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNumber == accNum && accounts[i].isActive && accounts[i].password == password) {
            return true;
        }
    }
    return false;
}
