#include <iostream>

#include "PersonalBudgetApp.h"

using namespace std;

int main() {

    PersonalBudgetApp personalBudgetApp ("users.xml", "transaction.xml");

    char choice;

    while (true) {
        if (!personalBudgetApp.isUserLoggedIn()) {
            choice = personalBudgetApp.selectOptionFromMainMenu();

            switch (choice) {
            case '1':
                personalBudgetApp.registerNewUser();
                break;
            case '2':
                personalBudgetApp.loginUser();
                break;
            case '9':
                exit(0);
                break;
            default:
                cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
                system("pause");
                break;
            }
        } else {
            choice = personalBudgetApp.selectOptionFromBudgetMenu();

            switch (choice) {
            case '1':
                personalBudgetApp.addIncome();
                break;
            case '2':
                personalBudgetApp.addExpense();
                break;
            case '3':
                personalBudgetApp.displayCurrentMonthBalanceSheet();
                break;
            case '4':
                //personalBudgetApp.displayPreviousMonthsBalanceSheet();
                break;
            case '5':
                //personalBudgetApp.displayBalanceSheetFromSelectedTimePeriod();
                break;
            case '6':
                personalBudgetApp.changeUserPassword();
                break;
            case '7':
                personalBudgetApp.logoutUser();
                break;
            }
        }
    }
    return 0;

}



