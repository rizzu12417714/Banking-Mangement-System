

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

// ---------------------- Account Class ----------------------
class Account {
private:
    int accNo;
    char name[50];        // fixed-size array (safe for binary file storage)
    char accType[15];     // Saving / Current
    double balance;

public:
    // Create a new account
    void createAccount() {
        string tempName, tempType;

        cout << "\n===== CREATE NEW ACCOUNT =====\n";
        cout << "Enter Account Number   : ";
        cin >> accNo;
        cin.ignore();
        cout << "Enter Account Holder Name : ";
        getline(cin, tempName);
        cout << "Enter Account Type (Saving/Current) : ";
        cin >> tempType;
        cout << "Enter Initial Deposit Amount : ";
        cin >> balance;

        // Safely copy into fixed-size arrays (avoids overflow)
        strncpy(name, tempName.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        strncpy(accType, tempType.c_str(), sizeof(accType) - 1);
        accType[sizeof(accType) - 1] = '\0';

        if (balance < 0) {
            cout << "Initial deposit cannot be negative! Setting balance to 0.\n";
            balance = 0;
        }
        cout << "\nAccount Created Successfully!\n";
    }

    void showAccount() const {
        cout << left;
        cout << setw(12) << accNo
             << setw(20) << name
             << setw(12) << accType
             << setw(10) << fixed << setprecision(2) << balance << endl;
    }

    void modifyAccount() {
        string tempName, tempType;

        cout << "\nModify details for Account No: " << accNo << endl;
        cout << "Enter New Name       : ";
        cin.ignore();
        getline(cin, tempName);
        cout << "Enter New Account Type (Saving/Current) : ";
        cin >> tempType;

        strncpy(name, tempName.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        strncpy(accType, tempType.c_str(), sizeof(accType) - 1);
        accType[sizeof(accType) - 1] = '\0';

        cout << "Account details updated successfully!\n";
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            return false; // insufficient balance
        }
        balance -= amount;
        return true;
    }

    int getAccNo() const { return accNo; }
    string getName() const { return string(name); }
    double getBalance() const { return balance; }

    static void showHeader() {
        cout << left;
        cout << setw(12) << "Acc No"
             << setw(20) << "Name"
             << setw(12) << "Type"
             << setw(10) << "Balance" << endl;
        cout << "---------------------------------------------------\n";
    }
};

// ---------------------- Banking System Class ----------------------
class BankingSystem {
private:
    const string FILENAME = "accounts.dat";

public:
    void mainMenu();
    void createAccount();
    void depositAmount();
    void withdrawAmount();
    void balanceEnquiry();
    void showAllAccounts();
    void modifyAccount();
    void deleteAccount();
    bool checkAccountExists(int accNo);
};

// ---------------------- Create Account ----------------------
void BankingSystem::createAccount() {
    Account acc;
    acc.createAccount();

    fstream file;
    file.open(FILENAME, ios::app | ios::binary);
    file.write((char*)&acc, sizeof(Account));
    file.close();

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Deposit ----------------------
void BankingSystem::depositAmount() {
    int accNo;
    double amount;
    bool found = false;

    cout << "\n===== DEPOSIT MONEY =====\n";
    cout << "Enter Account Number : ";
    cin >> accNo;

    fstream file;
    file.open(FILENAME, ios::in | ios::out | ios::binary);
    Account acc;

    while (file.read((char*)&acc, sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            cout << "Enter Amount to Deposit : ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!\n";
            } else {
                acc.deposit(amount);
                int pos = (-1) * (int)sizeof(Account);
                file.seekp(pos, ios::cur);
                file.write((char*)&acc, sizeof(Account));
                cout << "\nAmount Deposited Successfully!\n";
                cout << "New Balance: " << fixed << setprecision(2) << acc.getBalance() << endl;
            }
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Account not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Withdraw ----------------------
void BankingSystem::withdrawAmount() {
    int accNo;
    double amount;
    bool found = false;

    cout << "\n===== WITHDRAW MONEY =====\n";
    cout << "Enter Account Number : ";
    cin >> accNo;

    fstream file;
    file.open(FILENAME, ios::in | ios::out | ios::binary);
    Account acc;

    while (file.read((char*)&acc, sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            cout << "Enter Amount to Withdraw : ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!\n";
            } else if (acc.withdraw(amount)) {
                int pos = (-1) * (int)sizeof(Account);
                file.seekp(pos, ios::cur);
                file.write((char*)&acc, sizeof(Account));
                cout << "\nAmount Withdrawn Successfully!\n";
                cout << "New Balance: " << fixed << setprecision(2) << acc.getBalance() << endl;
            } else {
                cout << "\nInsufficient Balance!\n";
            }
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Account not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Balance Enquiry ----------------------
void BankingSystem::balanceEnquiry() {
    int accNo;
    bool found = false;

    cout << "\n===== BALANCE ENQUIRY =====\n";
    cout << "Enter Account Number : ";
    cin >> accNo;

    fstream file;
    file.open(FILENAME, ios::in | ios::binary);
    Account acc;

    while (file.read((char*)&acc, sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            cout << "\n--------- Account Details ---------\n";
            Account::showHeader();
            acc.showAccount();
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Account not found!\n";
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Show All Accounts ----------------------
void BankingSystem::showAllAccounts() {
    fstream file;
    file.open(FILENAME, ios::in | ios::binary);
    Account acc;
    bool any = false;

    cout << "\n===== ALL ACCOUNTS =====\n";
    Account::showHeader();

    while (file.read((char*)&acc, sizeof(Account))) {
        acc.showAccount();
        any = true;
    }
    file.close();

    if (!any) {
        cout << "No accounts found!\n";
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Modify Account ----------------------
void BankingSystem::modifyAccount() {
    int accNo;
    bool found = false;

    cout << "\n===== MODIFY ACCOUNT =====\n";
    cout << "Enter Account Number : ";
    cin >> accNo;

    fstream file;
    file.open(FILENAME, ios::in | ios::out | ios::binary);
    Account acc;

    while (file.read((char*)&acc, sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            acc.modifyAccount();
            int pos = (-1) * (int)sizeof(Account);
            file.seekp(pos, ios::cur);
            file.write((char*)&acc, sizeof(Account));
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Account not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Delete Account ----------------------
void BankingSystem::deleteAccount() {
    int accNo;
    bool found = false;

    cout << "\n===== DELETE ACCOUNT =====\n";
    cout << "Enter Account Number to Delete : ";
    cin >> accNo;

    fstream file, tempFile;
    file.open(FILENAME, ios::in | ios::binary);
    tempFile.open("temp.dat", ios::out | ios::binary);

    Account acc;
    while (file.read((char*)&acc, sizeof(Account))) {
        if (acc.getAccNo() != accNo) {
            tempFile.write((char*)&acc, sizeof(Account));
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    remove(FILENAME.c_str());
    rename("temp.dat", FILENAME.c_str());

    if (found) {
        cout << "\nAccount Deleted Successfully!\n";
    } else {
        cout << "\nAccount not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ---------------------- Main Menu ----------------------
void BankingSystem::mainMenu() {
    int choice;

    do {
        system("clear || cls");
        cout << "=====================================================\n";
        cout << "|            BANKING MANAGEMENT SYSTEM             |\n";
        cout << "=====================================================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Balance Enquiry\n";
        cout << "5. Show All Accounts\n";
        cout << "6. Modify Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "=====================================================\n";
        cout << "Enter your choice (1-8) : ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositAmount(); break;
            case 3: withdrawAmount(); break;
            case 4: balanceEnquiry(); break;
            case 5: showAllAccounts(); break;
            case 6: modifyAccount(); break;
            case 7: deleteAccount(); break;
            case 8:
                cout << "\nThank you for using Banking Management System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                cin.ignore();
                cin.get();
        }
    } while (choice != 8);
}

// ---------------------- Main Function ----------------------
int main() {
    BankingSystem bank;
    bank.mainMenu();
    return 0;
}