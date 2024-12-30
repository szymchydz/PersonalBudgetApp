#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>

#include "Transaction.h"
#include "TransactionFile.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "Type.h"

using namespace std;

class TransactionManager {
    const int LOGGED_IN_USER_ID;
    vector<Transaction> incomes;
    vector<Transaction> expenses;
    vector<Transaction> transactions;
    TransactionFile incomesFile;
    TransactionFile expensesFile;

    DateMethods dateMethods;

    Transaction addTransactionDetails(const Type& type);
    char selectOptionFromDateMenu();
    void sortDateIncomes();
    void sortDateExpenses();
    string displayTransactions(int number, const Type& type);
    double calculateBalanceSheet(int startDate, int endDate, const Type& type);
    void displayCalculateBalanceSheet(int startDate, int endDate);

public:
    TransactionManager(string fileNameWithIncomes, string fileNameWithExpenses, int loggedInUserId)
    : LOGGED_IN_USER_ID(loggedInUserId), incomesFile(fileNameWithIncomes), expensesFile(fileNameWithExpenses) {

        cout << "Ladowanie transakcji dla uzytkownika ID: " << LOGGED_IN_USER_ID << endl;
        cout << "ID zalogowanego uzytkownika: " << loggedInUserId << endl;

        vector<Transaction> incomeTransactions = incomesFile.loadTransactionFromFiles(LOGGED_IN_USER_ID, fileNameWithIncomes, fileNameWithExpenses);
        vector<Transaction> expenseTransactions = expensesFile.loadTransactionFromFiles(LOGGED_IN_USER_ID, fileNameWithIncomes, fileNameWithExpenses);

        transactions.insert(transactions.end(), incomeTransactions.begin(), incomeTransactions.end());
        transactions.insert(transactions.end(), expenseTransactions.begin(), expenseTransactions.end());

        cout << "Zaladowano " << incomeTransactions.size() << " przychodow i " << expenseTransactions.size() << " wydatkow." << endl;
        system("pause");
    }

    void addIncome();
    void addExpense();
    void displayCurrentMonthBalanceSheet();
    void displayPreviousMonthBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();
};

#endif // TRANSACTIONMANAGER_H
