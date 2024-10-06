#include "PersonalBudgetApp.h"


void PersonalBudgetApp :: registerNewUser() {
    userManager.addUser();
}

void PersonalBudgetApp :: loginUser() {

    userManager.loginUser();
    if (userManager.isUserLoggedIn()) {
        transactionManager = new TransactionManager (FILE_NAME_WITH_TRANSACTIONS, userManager.getLoggedInUserId());
    }
}

bool PersonalBudgetApp :: isUserLoggedIn() {
    userManager.isUserLoggedIn();
}

void PersonalBudgetApp :: logoutUser() {

    userManager.logoutUser();
    delete transactionManager;
    transactionManager = NULL;
}

void PersonalBudgetApp :: changeUserPassword() {
    userManager.changeUserPassword();
}

void PersonalBudgetApp :: addIncome() {
    if(userManager.isUserLoggedIn()) {
        transactionManager->addIncome();
    } else {
        cout << "Aby dodac zarobek, nalezy najpierw sie zalogowac." << endl;
        system("pause");
    }
}
void PersonalBudgetApp :: addExpense() {
    if(userManager.isUserLoggedIn()) {
        transactionManager->addExpense();
    } else {
        cout << "Aby dodac zarobek, nalezy najpierw sie zalogowac." << endl;
        system("pause");
    }
}

/*void PersonalBudgetApp::displayCurrentMonthsBalanceSheet() {

    transactionManager->displayCurrentMonthsBalanceSheet();
}

void PPersonalBudgetApp::displayPreviousMonthsBalanceSheet() {

    transactionManager->displayPreviousMonthsBalanceSheet();
}

void PPersonalBudgetApp::displayBalanceSheetFromSelectedTimePeriod() {

    transactionManager->displayBalanceSheetFromSelectedTimePeriod();
}

bool PersonalBudgetApp::isUserLoggedIn() {

    return userManager.isUserLoggedIn();
}*/


char PersonalBudgetApp::selectOptionFromMainMenu() {

    char choice;

    system("cls");
    cout << "    >>> MENU  GLOWNE <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Koniec programu" << endl;
    cout << "---------------------------" << endl;
    cout << "Twoj wybor: ";
    choice = AuxiliaryMethods::getchar();

    return choice;
}

char PersonalBudgetApp::selectOptionFromBudgetMenu() {

    char choice;

    system("cls");
    cout << " >>> MENU UZYTKOWNIKA <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Dodaj przychod" << endl;
    cout << "2. Dodaj wydatek" << endl;
    cout << "3. Bilans z biezacego miesiaca" << endl;
    cout << "4. Bilans z poprzedniego miesiaca" << endl;
    cout << "5. Bilans z wybranego okresu" << endl;
    cout << "---------------------------" << endl;
    cout << "6. Zmien haslo" << endl;
    cout << "7. Wyloguj sie" << endl;
    cout << "---------------------------" << endl;
    cout << "Twoj wybor: ";
    choice = AuxiliaryMethods::getchar();

    return choice;
}
