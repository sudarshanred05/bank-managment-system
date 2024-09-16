#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Account {
    static int accountCounter;
    int accountNumber;
    string name;
    char gender;
    int age;
    char accountType;
    double balance;

public:
   
    Account()
    {
        accountNumber = accountCounter;
        balance = 0;
    }

    void openAccount() {
        cout << "Enter name: ";
        getline(cin >> ws, name);

        char validGenderInput;
        do {
            cout << "Enter gender (M/F): ";
            cin >> gender;
            validGenderInput = (gender == 'M' || gender == 'm' || gender == 'f' || gender == 'F');
            if (!validGenderInput) {
                cout << "Invalid gender input. Please enter M or F." << endl;
            }
        } while (!validGenderInput);

        cout << "Enter age: ";
        cin >> age;

        char validAccountTypeInput;
        do {
            cout << "Enter account type  S-savings or C-current (S/C): ";
            cin >> accountType;
            validAccountTypeInput = (accountType == 's' || accountType == 'S' || accountType == 'C' || accountType == 'c');
            if (!validAccountTypeInput) {
                cout << "Invalid account type input. Please enter S or C." << endl;
            }
        } while (!validAccountTypeInput);

        if (accountType == 's' || accountType == 'S') {
            cout << "Minimum deposit for Savings account is 500." << endl;
            do {
                cout << "Enter initial deposit amount (>= 500): ";
                cin >> balance;
            } while (balance < 500);
        }

        cout << "Your account number is: " << accountCounter << endl;
        accountCounter++;
    }

    void displayAccountDetails() const {
        cout << "Account Holder: " << name << endl;
        cout << "Gender: " << gender << endl;
        cout << "Age: " << age << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void withdraw() {
        double amount;
        cout << "Enter withdrawal amount: $";
        cin >> amount;

        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Remaining balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
        }
    }

    void deposit() {
        double amount;
        cout << "Enter deposit amount: $";
        cin >> amount;

        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void closeAccount(vector<Account>& accounts) {
        bool found = false;
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == this->accountNumber) {
                accounts.erase(it);
                cout << "Account closed successfully." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Account not found." << endl;
        }
    }

    void transferAmount(Account& otherAccount) {
        double amount;
        cout << "Enter transfer amount: $";
        cin >> amount;

        if (amount > 0 && amount <= balance) {
            balance -= amount;
            otherAccount.balance += amount;  // Update recipient account balance
            cout << "Transfer successful. Remaining balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid transfer amount or insufficient balance." << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

int Account::accountCounter = 1;

int main() {
    vector<Account> accounts;

    cout << "\n\n\n:::::: :::::: :::::: :::::: :::::: :::::: :::::: Welcome to Bank Management system :::::: :::::: :::::: :::::: :::::: :::::: :::::::\n\n";

    int choice;

    do {
        cout << "\n========   Banking System Menu ========\n" << endl;
        cout << "1. Open Account\n2. Withdraw\n3. Deposit\n4. Show All Accounts\n5. Close Account\n6. Transfer Amount\n7. Show Balance\n8. Exit\n";
        cout << "\n=======================================\n" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Account newAccount;
                newAccount.openAccount();
                accounts.push_back(newAccount);
                cout << "Account added successfully" << endl;
                break;
            }
            case 2: {
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;

                bool found = false;
                for (auto it = accounts.begin(); it != accounts.end(); ++it) {
                    if (it->getAccountNumber() == accountNumber) {
                        it->withdraw();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 3: {
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;

                bool found = false;
                for (auto it = accounts.begin(); it != accounts.end(); ++it) {
                    if (it->getAccountNumber() == accountNumber) {
                        it->deposit();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 4: {
                cout << "\n=== All Accounts in  ===" << endl;
                for (const Account& acc : accounts) {
                    acc.displayAccountDetails();
                    cout << "-------------------------" << endl;
                }
                break;
            }

            case 5: {
                int accountNumber;
                cout << "Enter account number to close: ";
                cin >> accountNumber;

                bool found = false;
                for (auto it = accounts.begin(); it != accounts.end(); ++it) {
                    if (it->getAccountNumber() == accountNumber) {
                        it->closeAccount(accounts);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 6: {
                int accountNumber1, accountNumber2;
                cout << "Enter your account number: ";
                cin >> accountNumber1;
                cout << "Enter recipient account number: ";
                cin >> accountNumber2;

                bool found1 = false, found2 = false;
            
                for (auto it = accounts.begin(); it != accounts.end(); ++it) {
                    if (it->getAccountNumber() == accountNumber1) {
                        found1 = true;
                        for (auto re = accounts.begin(); re != accounts.end(); ++re) {
                            if (re->getAccountNumber() == accountNumber2) {
                                found2 = true;
                                it->transferAmount(*re);
                                goto l1;
                            }
                        }
                    }   
                }
                if (!found1 || !found2) {
                    cout << "One or both accounts not found." << endl;
                }
              l1:  break;
            }
            
            case 7: {
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;

                bool found = false;
                for (const Account& acc : accounts) {
                    if (acc.getAccountNumber() == accountNumber) {
                        cout << "Balance for account " << accountNumber << ": $" << fixed << setprecision(2) << acc.getBalance() << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 8:
                cout << "Exiting program. Thank you!\n\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n\n";
        }
    } while (choice != 8);

    return 0;
}