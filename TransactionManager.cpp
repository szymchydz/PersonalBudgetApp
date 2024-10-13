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
        date = dateMethods.getTimeFromSystem("%Y-%m-%d");
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
    transactions.push_back(income);

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
    transactions.push_back(expense);

     if(transactionFile.addTransactionToFile(expense, EXPENSE) == true) {
        cout << "Nowy wydatek zostal dodany do pliku." << endl;
    } else
        cout << "Blad. Nie udalo sie dodac nowego wydatku do pliku." << endl;
        system("pause");
}

void TransactionManager::sortDateIncomes() {

    sort(transactions.begin(), transactions.end(), [](const Transaction& lhs, const Transaction& rhs) {
        return lhs.date < rhs.date;
    });
}
void TransactionManager::sortDateExpenses() {

    sort(transactions.begin(), transactions.end(), [](const Transaction& lhs, const Transaction& rhs) {
        return lhs.date < rhs.date;
    });
}

string TransactionManager::displayTransactions(int number, const Type &type) {

    string amount;
    switch(type) {

    case INCOME:
        cout << "-------------------------------------------------------------" << endl;
        cout << "Numer ID: " << transactions[number].id << endl;
        cout << "Data: ";
        dateMethods.displayDate(DateMethods::changeDateWithoutHypenToDateWithHyphen(AuxiliaryMethods::convertIntToString(transactions[number].date)));
        cout << endl << "Opis: " << transactions[number].item << endl;
        cout << "Wartosc [PLN]: " << transactions[number].amount << endl;
        amount = transactions[number].amount;
        break;

    case EXPENSE:
        cout << "-------------------------------------------------------------" << endl;
        cout << "Numer ID: " << transactions[number].id << endl;
        cout << "Data: ";
        dateMethods.displayDate(DateMethods::changeDateWithoutHypenToDateWithHyphen(AuxiliaryMethods::convertIntToString(transactions[number].date)));
        cout << endl << "Opis: " << transactions[number].item << endl;
        cout << "Wartosc [PLN]: " << transactions[number].amount << endl;
        amount = transactions[number].amount;
        break;

    }
    return amount;

}

double TransactionManager::calculateBalanceSheet(int startDate, int endDate, const Type& type) {

    string typeDescription;
    double sumTransactions = 0;

    switch(type) {

    case INCOME:
        typeDescription = "PRZYCHODY";

        if(!transactions.empty()) {
            cout << "         <<<" << typeDescription << ">>>         " << endl;

            for (int i =0; i < (int) transactions.size(); i++) {
                if (startDate <= transactions[i].date) {
                    if(endDate >= transactions[i].date)
                        sumTransactions += (AuxiliaryMethods::convertStringToDouble(displayTransactions(i,INCOME)));
                }
            }
            cout << endl;
        } else {
            cout << endl << typeDescription << " NIE ISTNIEJA." << endl;
        }
        break;

    case EXPENSE:
        typeDescription = "WYDATKI";

        if(!transactions.empty()) {
            cout << "         <<<" << typeDescription << ">>>         " << endl;

            for (int i =0; i < (int) transactions.size(); i++) {

                if (startDate <= transactions[i].date) {
                    if(endDate >= transactions[i].date) {
                        sumTransactions+= (AuxiliaryMethods::convertStringToDouble(displayTransactions(i, EXPENSE)));
                    }
                }
            }
            cout << endl;
        } else {
            cout << endl << typeDescription << " NIE ISTNIEJA." << endl;
        }
        break;
    }

    return sumTransactions;
}

void TransactionManager::displayCalculateBalanceSheet(int startDate, int endDate) {

    sortDateIncomes();
    sortDateExpenses();

    system("cls");
    cout << "POKAZ SALDO" << endl;
    cout << "WYBRANY PRZEDZIAL CZASOWY: " ;
    dateMethods.displayDate(DateMethods::changeDateWithHypenToDateWithoutHyphen(AuxiliaryMethods::convertIntToString(startDate)));
    cout << " DO " ;
    dateMethods.displayDate(DateMethods::changeDateWithoutHypenToDateWithHyphen(AuxiliaryMethods::convertIntToString(endDate)));
    cout << endl << endl;
    double incomesSum = calculateBalanceSheet(startDate, endDate, INCOME);
    double expensesSum = calculateBalanceSheet(startDate, endDate, EXPENSE);

    cout << "-------------------------------------------------------------------" << endl;
    cout << "Suma przychodow w wybranym przedziale czasowym: " << incomesSum << " PLN." << endl;
    cout << "Suma wydatkow w wybranym przedziale czasowym: " << expensesSum << " PLN." <<endl;
    cout << "Saldo w wybranym przedziale czasowym: " << incomesSum - expensesSum << " PLN." << endl;

}


void TransactionManager::displayCurrentMonthBalanceSheet() {

string currentDate = dateMethods.getTimeFromSystem("%Y-%m-%d");
    cout << "Current Date: " << currentDate << endl;

    string startDate = dateMethods.getStartDate(currentDate);
    cout << "Start Date: " << startDate << endl;

    string endDate = dateMethods.getEndDate(currentDate);
    cout << "End Date: " << endDate << endl;

    displayCalculateBalanceSheet(AuxiliaryMethods::convertStringToInt(startDate),
                                 AuxiliaryMethods::convertStringToInt(endDate));

    system("pause");
}
