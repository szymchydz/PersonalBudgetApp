#ifndef PERSONALBUDGETAPP_H
#define PERSONALBUDGETAPP_H

#include <iostream>
#include <string>
#include "UserManager.h"
#include "TransactionManager.h"
#include "AuxiliaryMethods.h"

using namespace std;

class PersonalBudgetApp {
    UserManager userManager;
    TransactionManager *transactionManager;
    const string FILE_NAME_WITH_TRANSACTIONS;

public:
    PersonalBudgetApp(const string &fileNameWithUsers, const string &fileNameWithTransactions);
    ~PersonalBudgetApp();

    void registerNewUser();
    void loginUser();
    bool isUserLoggedIn();
    void logoutUser();
    void changeUserPassword();
    void addIncome();
    void addExpense();
    void displayCurrentMonthBalanceSheet();
    void displayPreviousMonthsBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();

    char selectOptionFromMainMenu();
    char selectOptionFromBudgetMenu();
};

#endif // PERSONALBUDGETAPP_H
