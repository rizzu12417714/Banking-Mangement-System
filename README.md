# Banking-Mangement-System


A console-based banking management system written in C++. The program stores account records in a binary data file and provides basic banking operations through a menu-driven interface.

## Features

- Create a new bank account
- Display all accounts
- Search for an account by account number
- Deposit money
- Withdraw money with balance validation
- Modify account details
- Delete an account
- Persistent local storage using a binary file

## Project Files

| File | Description |
| --- | --- |
| `bank.cpp` | Main and recommended implementation. Uses `account.dat` for storage. |
| `bank2.cpp` | Alternate implementation using the `Account` and `BankingSystem` classes. |
| `bank3.cpp` | Safer alternate implementation using fixed-size character arrays for binary storage. |
| `account.dat` | Binary account data created by `bank.cpp` at runtime. |
| `accounts.dat` | Binary account data used by `bank2.cpp` and `bank3.cpp`. |

## Requirements

- Windows, Linux, or macOS
- A C++ compiler with C++11 or later support
- MinGW g++ on Windows, or any compatible `g++` compiler

## Build and Run

### Windows with MinGW

From the project folder, compile the recommended program:

```powershell
g++ -std=c++11 -Wall -Wextra -g bank.cpp -o bank.exe
```

Run it with:

```powershell
.\bank.exe
```

If MinGW is installed at `C:\MinGW\bin`, use:

```powershell
& 'C:\MinGW\bin\g++.exe' -std=c++11 -Wall -Wextra -g bank.cpp -o bank.exe
.\bank.exe
```

### Linux or macOS

```bash
g++ -std=c++11 -Wall -Wextra -g bank.cpp -o bank
./bank
```

## Usage

After starting the program, select an option from the main menu:

1. Open a new account
2. Show all accounts
3. Search for an account
4. Deposit money
5. Withdraw money
6. Delete an account
7. Modify account details
8. Exit

Account data is saved automatically in `account.dat`, so it remains available the next time the program is run.

## Sample Output

Selecting `5. Show All Accounts` displays the stored accounts in a table:

```text
===== ALL ACCOUNTS =====
Acc No      Name                Type        Balance
---------------------------------------------------
887255      .                   Saving      6000.00
8855        Rizzu Khan          Saving      51000.00
88          Rizzu Khan          Saving      3000.00
889         Rizzu Khan          Saving      2200.00

Press Enter to continue...
```

### Create Account

```text
===== CREATE NEW ACCOUNT =====
Enter Account Number       : 889
Enter Account Holder Name  : Rizzu Khan
Enter Account Type (Saving/Current) : Saving
Enter Initial Deposit Amount : 500

Account Created Successfully!
```

### Deposit Money

```text
===== DEPOSIT MONEY =====
Enter Account Number : 889
Enter Amount to Deposit : 2000

Amount Deposited Successfully!
New Balance: 2500.00
```

### Withdraw Money

```text
===== WITHDRAW MONEY =====
Enter Account Number : 889
Enter Amount to Withdraw : 300

Amount Withdrawn Successfully!
New Balance: 2200.00
```

### Balance Enquiry

```text
===== BALANCE ENQUIRY =====
Enter Account Number : 889

--------- Account Details ---------
Acc No      Name                Type        Balance
---------------------------------------------------
889         Rizzu Khan          Saving      2200.00
```

## Notes

- Do not open the binary data files in a text editor.
- Keep the executable and its data file in the same directory.
- The program is intended for learning and demonstration purposes and is not suitable for real banking or production use.
