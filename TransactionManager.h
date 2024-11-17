#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"
#include "TransactionFile.h"
#include "DateMethods.h"
#include "AuxiliaryMethods.h"
#include "Type.h"

class TransactionManager {
    const int LOGGED_IN_USER_ID;
    std::vector<Transaction> incomes;
    std::vector<Transaction> expenses;
    TransactionFile transactionFile;

    DateMethods dateMethods;

    Transaction addTransactionDetails(const Type &type);
    char selectOptionFromDateMenu();
    void sortDateIncomes();
    void sortDateExpenses();
    string displayTransactions(int number, const Type &type);
    double calculateBalanceSheet(int startDate, int endDate, const Type &type);
    void displayCalculateBalanceSheet(int startDate, int endDate);

public:
    TransactionManager(const std::string& fileNameWithTransactions, int loggedInUserId);

    const vector<Transaction>& getIncomes() const { return incomes; }
    const vector<Transaction>& getExpenses() const { return expenses; }

    void addIncome();
    void addExpense();
    void displayCurrentMonthBalanceSheet();
    void displayPreviousMonthBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();
};

#endif // TRANSACTIONMANAGER_H
