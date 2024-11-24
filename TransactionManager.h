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
    vector <Transaction> incomes;
    vector <Transaction> expenses;
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
    TransactionManager(string fileNameWithTransactions, int loggedInUserId)
    : LOGGED_IN_USER_ID(loggedInUserId), transactionFile(fileNameWithTransactions) {
    cout << "Ladowanie transakcji dla uzytkownika ID: " << LOGGED_IN_USER_ID << endl;
    cout << "Id zalogowanego uzytkownika: " << loggedInUserId << endl;
    incomes = transactionFile.loadTransactionFromFile(LOGGED_IN_USER_ID);
    expenses = transactionFile.loadTransactionFromFile(LOGGED_IN_USER_ID);
    cout << "Zaladowano " << incomes.size() << " przychodow i " << expenses.size() << " wydatkow." << endl;
    system ("pause");
};

    void addIncome();
    void addExpense();
    void displayCurrentMonthBalanceSheet();
    void displayPreviousMonthBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();
};

#endif // TRANSACTIONMANAGER_H
