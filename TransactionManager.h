#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>

#include "Transaction.h"
#include "TransactionFile.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "Type.h"

using namespace std;

class TransactionManager {
    const int LOGGED_IN_USER_ID;
    vector <Transaction> transactions;
    TransactionFile transactionFile;
    DateMethods dateMethods;

    Transaction addTransactionDetails(const Type &type);

    char selectOptionFromDateMenu();
    void sortDateIncomes();
    void sortDateExpenses();
    string displayTransactions(int number, const Type &type);
    double calculateBalanceSheet(int startDate, int endDate, const Type& type);
    void displayCalculateBalanceSheet(int startDate, int endDate);


public:

    TransactionManager (string fileNameWithTransactions, int loggedInUserId)
        : LOGGED_IN_USER_ID(loggedInUserId), transactionFile(fileNameWithTransactions) {
       transactions = transactionFile.loadTransactionFromFile(LOGGED_IN_USER_ID);
    };

    void addIncome();
    void addExpense();
    void displayCurrentMonthBalanceSheet();
    void displayPreviousMonthBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();
};

#endif // TRANSACTIONMANAGER_H
