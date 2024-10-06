#ifndef PERSONALBUDGETAPP_H
#define PERSONALBUDGETAPP_H

#include <iostream>
#include <string>

#include "UserManager.h"
#include "TransactionManager.h"

using namespace std;

class PersonalBudgetApp {

    UserManager userManager;
    TransactionManager *transactionManager;
    const string FILE_NAME_WITH_TRANSACTIONS;

public:
    PersonalBudgetApp(const string& fileNameWithUsers, const string& fileNameWithTransactions)
        : userManager(fileNameWithUsers), FILE_NAME_WITH_TRANSACTIONS(fileNameWithTransactions) {
    };

    ~PersonalBudgetApp() {
      delete transactionManager;
      transactionManager = NULL;
    };

    void registerNewUser();
    void loginUser();
    bool isUserLoggedIn();
    void logoutUser();
    void changeUserPassword();
    void addIncome();
    void addExpense();
    /*void displayCurrentMonthsBalanceSheet();
    void displayPreviousMonthsBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();*/

    char selectOptionFromMainMenu();
    char selectOptionFromBudgetMenu();

};

#endif // PERSONALBUDGETAPP_H
