#include "TransactionManager.h"


char TransactionManager::selectOptionFromDateMenu() {

    char choice;

    cout << "Dotyczy dnia dzisiejszego czy chcesz dodac z inna data? " << endl;
    cout << "1 - Dzisiejsza data" << endl;
    cout << "2 - Inna data" << endl;
    cout << "9 - Powrot " << endl;
    cout << endl << "Twoj wybor: ";
    choice = AuxiliaryMethods::getchar();

    return choice;
}

Transaction TransactionManager::addTransactionDetails(const Type &type) {

    Transaction transaction;
    string typeDescription, date;
    char choice;

    switch(type) {

    case INCOME:
        transaction.id = transactionFile.currentTransactionId + 1;
        typeDescription = "przychod";
        break;
    case EXPENSE:
        transaction.id = transactionFile.currentTransactionId +1;
        typeDescription = "wydatek";
        break;
    }

    transaction.userId = LOGGED_IN_USER_ID;

    choice = selectOptionFromDateMenu();

    switch (choice) {

    case '1':
        date = dateMethods.getTimeFromSystem();
        break;
    case '2':
        do {
            system("cls");
            cout << "Prosze o wpisanie daty w formacie rrrr-mm-dd. Zostanie dodany " << typeDescription << " do Budzetu. Data musi miescic sie w zakresie czasowym od 2000-01-01 do maksymalnie ostatniego dnia biezacego miesiaca." << endl << endl;
            date = AuxiliaryMethods::readLine();
            if (dateMethods.checkFormatDateIsCorrect(date) == false)
                cout << "Niepoprawny format daty lub niepoprawnie podany zakres czasowy." << endl;
        } while (dateMethods.checkFormatDateIsCorrect(date)== false);
        break;
    case '9':
        exit(0);
        break;
    default:
        cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
        system("pause");
        break;
    }
    transaction.date = AuxiliaryMethods::convertStringToInt(DateMethods::changeDateWithHypenToDateWithoutHyphen(date));
    system("cls");
    cout << "Prosze o wpisanie czego dotyczy " << typeDescription << ": " << endl;
    transaction.item = AuxiliaryMethods::readLine();

    cout << "Prosze o wpisanie wielkosci z dokladnoscia do dwoch miejsc dziesietnych w zlotych: " << endl;
    transaction.amount = stod(AuxiliaryMethods::validateInput(AuxiliaryMethods::readLine()));

    return transaction;

}

void TransactionManager::addIncome() {

    Transaction income;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO PRZYCHODU <<<" << endl << endl;
    income = addTransactionDetails(INCOME);
    incomes.push_back(income);

    if(transactionFile.addTransactionToFile(income, INCOME) == true) {
        cout << "Nowy przychod zostal dodany do pliku." << endl;
    } else
        cout << "Blad. Nie udalo sie dodac nowego przychodu do pliku." << endl;

    system("pause");
}

void TransactionManager::addExpense() {

    Transaction expense;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO WYDATKU <<<" << endl << endl;
    expense = addTransactionDetails(EXPENSE);
    expenses.push_back(expense);

     if(transactionFile.addTransactionToFile(expense, EXPENSE) == true) {
        cout << "Nowy wydatek zostal dodany do pliku." << endl;
    } else
        cout << "Blad. Nie udalo sie dodac nowego wydatku do pliku." << endl;
        system("pause");
}

