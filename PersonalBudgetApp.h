#ifndef PERSONALBUDGETAPP_H
#define PERSONALBUDGETAPP_H

#include <iostream>
#include <string>

#include "UserManager.h"
//#include "TransactionManager.h"

using namespace std;

class PersonalBudgetApp {

    UserManager userManager;
    //TransactionManager *transactionManager;
    const string FILE_NAME_WITH_TRANSACTIONS;
    //const string FILE_NAME_WITH_EXPENSES;

public:
    PersonalBudgetApp(string fileNameWithUsers) /*string fileNameWithTransactions*/
        : userManager(fileNameWithUsers)/*FILE_NAME_WITH_TRANSACTION(fileNameWithTransactions))*/ {
        //transactionManager = NULL;
    };

    ~PersonalBudgetApp() {
       // delete transactionManager;
        //transactionManager = NULL;
    };

    void registerNewUser();
    /*void loginUser();
    void logoutUser();
    void changePassword();
    void addIncome();
    void addExpense();
    void displayCurrentMonthsBalanceSheet();
    void displayPreviousMonthsBalanceSheet();
    void displayBalanceSheetFromSelectedTimePeriod();
    bool isUserLoggedIn();
    char selectOptionFromMainMenu();
    char selectOptionFromBudgetMenu();*/

};

#endif // PERSONALBUDGETAPP_H
