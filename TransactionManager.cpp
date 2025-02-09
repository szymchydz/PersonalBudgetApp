#include "TransactionManager.h"

int TransactionManager::loadLastTransactionId(const vector<Transaction>& transactions) {
    return transactions.empty() ? 0 : transactions.size();
}

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

    const vector<Transaction>& transactions = (type == INCOME) ? incomes : expenses;

    transaction.id = loadLastTransactionId(transactions) + 1;

    typeDescription = (type == INCOME) ? "przychod" : "wydatek";

    transaction.userId = LOGGED_IN_USER_ID;
    choice = selectOptionFromDateMenu();

    switch (choice) {
        case '1':
            date = dateMethods.getTimeFromSystem();
            break;
        case '2':
            do {
                system("cls");
                cout << "Prosze o wpisanie daty w formacie rrrr-mm-dd. Zostanie dodany "
                     << typeDescription
                     << " do Budzetu. Data musi miescic sie w zakresie czasowym od 2000-01-01 do maksymalnie ostatniego dnia biezacego miesiaca."
                     << endl << endl;
                date = AuxiliaryMethods::readLine();
                if (!dateMethods.checkFormatDateIsCorrect(date))
                    cout << "Niepoprawny format daty lub niepoprawnie podany zakres czasowy." << endl;
            } while (!dateMethods.checkFormatDateIsCorrect(date));
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
            system("pause");
            break;
    }

    transaction.date = AuxiliaryMethods::convertStringToInt(dateMethods.changeDateWithHyphenToDateWithoutHyphen(date));
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

    if (incomesFile.addTransactionToFile(income, INCOME)) {
        cout << "Nowy przychod zostal dodany do pliku." << endl;
    } else {
        cout << "Blad. Nie udalo sie dodac nowego przychodu do pliku." << endl;
    }

    cout << "Liczba przychodow: " << incomes.size() << endl;
    system("pause");
}

void TransactionManager::addExpense() {
    Transaction expense;

    system("cls");
    cout << " >>> DODAWANIE NOWEGO WYDATKU <<<" << endl << endl;
    expense = addTransactionDetails(EXPENSE);
    expenses.push_back(expense);

    if (expensesFile.addTransactionToFile(expense, EXPENSE)) {
        cout << "Nowy wydatek zostal dodany do pliku." << endl;
    } else {
        cout << "Blad. Nie udalo sie dodac nowego wydatku do pliku." << endl;
    }

    cout << "Liczba wydatkow: " << expenses.size() << endl;
    system("pause");
}

void TransactionManager::sortDateIncomes() {

    sort(incomes.begin(), incomes.end(), [](const Transaction& lhs, const Transaction& rhs) {
        return lhs.date < rhs.date;
    });
}
void TransactionManager::sortDateExpenses() {

    sort(expenses.begin(), expenses.end(), [](const Transaction& lhs, const Transaction& rhs) {
        return lhs.date < rhs.date;
    });
}

string TransactionManager::displayTransactions(int number, const Type &type) {
    string amount;
    switch(type) {

    case INCOME:
        cout << "-------------------------------------------------------------" << endl;
        cout << "Numer ID: " << incomes[number].id << endl;
        cout << "Data: ";
        dateMethods.displayDate(DateMethods::changeDateWithoutHyphenToDateWithHyphen(AuxiliaryMethods::convertIntToString(incomes[number].date)));
        cout << endl << "Opis: " << incomes[number].item << endl;
        cout << "Wartosc [PLN]: " << incomes[number].amount << endl;
        cout << endl;
        amount = to_string(incomes[number].amount);
        break;

    case EXPENSE:
        cout << "-------------------------------------------------------------" << endl;
        cout << "Numer ID: " << expenses[number].id << endl;
        cout << "Data: ";
        dateMethods.displayDate(DateMethods::changeDateWithoutHyphenToDateWithHyphen(AuxiliaryMethods::convertIntToString(expenses[number].date)));
        cout << endl << "Opis: " << expenses[number].item << endl;
        cout << "Wartosc [PLN]: " << expenses[number].amount << endl;
        cout << endl;
        amount = to_string(expenses[number].amount);
        break;

    }
    return amount;
}

double TransactionManager::calculateBalanceSheet(int startDate, int endDate, const Type& type) {
    if (startDate > endDate) {
        cout << "Blad! Data poczatkowa jest pozniejsza niz data koncowa." << endl;
        return 0.0;
    }

    double sumTransactions = 0.0;
    bool hasTransactions = false;

    switch (type) {
    case INCOME: {
        cout << "<<< PRZYCHODY >>>" << endl;
        for (size_t i = 0; i < incomes.size(); ++i) {
            if (startDate <= incomes[i].date && endDate >= incomes[i].date) {
                hasTransactions = true;
                string transactionString = displayTransactions(i, INCOME);
                double transactionValue = AuxiliaryMethods::convertStringToDouble(transactionString);
                sumTransactions += transactionValue;
            }
        }
        if (!hasTransactions) {
            cout << endl << "BRAK PRZYCHODOW !!" << endl << endl;
        }
        break;
    }
    case EXPENSE: {
        cout << "<<< WYDATKI >>>" << endl;
        for (size_t i = 0; i < expenses.size(); ++i) {
            if (startDate <= expenses[i].date && endDate >= expenses[i].date) {
                hasTransactions = true;
                string transactionString = displayTransactions(i, EXPENSE);
                double transactionValue = AuxiliaryMethods::convertStringToDouble(transactionString);
                sumTransactions += transactionValue;
            }
        }
        if (!hasTransactions) {
            cout << endl << "BRAK WYDATKOW !!" << endl << endl;
        }
        break;
    }
    default:
        cout <<  "Nieprawid³owy typ transakcji." << endl;
        return 0.0;
    }

    return sumTransactions;
}

void TransactionManager::displayCalculateBalanceSheet(int startDate, int endDate) {
    sortDateIncomes();
    sortDateExpenses();

    system("cls");
    cout << "BILANS" << endl;
    cout << "OKRES: ";
    dateMethods.displayDate(dateMethods.changeDateWithoutHyphenToDateWithHyphen(AuxiliaryMethods::convertIntToString(startDate)));
    cout << " <-> ";
    dateMethods.displayDate(dateMethods.changeDateWithoutHyphenToDateWithHyphen(AuxiliaryMethods::convertIntToString(endDate)));
    cout << endl << endl;

    double incomesSum = calculateBalanceSheet(startDate, endDate, INCOME);
    double expensesSum = calculateBalanceSheet(startDate, endDate, EXPENSE);

    cout << "-------------------------------------------------------------------" << endl;
    cout << "Suma przychodow w wybranym przedziale czasowym: " << incomesSum << " PLN." << endl;
    cout << "Suma wydatkow w wybranym przedziale czasowym: " << expensesSum << " PLN." << endl;
    cout << "Saldo w wybranym przedziale czasowym: " << incomesSum - expensesSum << " PLN." << endl;
}



void TransactionManager::displayCurrentMonthBalanceSheet() {

    string currentDate = dateMethods.getTimeFromSystem();
    string startDate =  (currentDate.substr(0,4) + currentDate.substr(5,2) + "01");
    string endDate = (currentDate.substr(0,4) + currentDate.substr(5,2) + AuxiliaryMethods::convertIntToString(dateMethods.checkNumberOfDaysPerMonth(dateMethods.getYearFromDate(currentDate),dateMethods.getMonthFromDate(currentDate))));
    displayCalculateBalanceSheet(AuxiliaryMethods::convertStringToInt(startDate), AuxiliaryMethods::convertStringToInt(endDate));

    system("pause");
}

void TransactionManager::displayPreviousMonthBalanceSheet() {

    string currentDate = dateMethods.getTimeFromSystem();
    string previousMonth = dateMethods.getPreviousMonthFromDate(currentDate);

    if (previousMonth=="12") {
        if (currentDate[3]=='0') {
            currentDate[2]--;
            currentDate[3]='9';
        } else
            currentDate[3]--;
    }
    string startDate = (currentDate.substr(0,4) + previousMonth + "01");
    string endDate = (currentDate.substr(0,4) + previousMonth + AuxiliaryMethods::convertIntToString(dateMethods.checkNumberOfDaysPerMonth(dateMethods.getYearFromDate(currentDate),AuxiliaryMethods::convertStringToInt(previousMonth))));

    displayCalculateBalanceSheet(AuxiliaryMethods::convertStringToInt(startDate), AuxiliaryMethods::convertStringToInt(endDate));

    system("pause");
}

void TransactionManager::displayBalanceSheetFromSelectedTimePeriod() {

    string enteredStartDate, enteredEndDate;

    do {
        cout << "Wprowadz date w formacie rrrr-mm-dd od ktorej chcesz rozpoczac bilans." << endl;
        cout << "Data musi miescic sie w zakresie czasowym od 2000-01-01 do maksymalnie ostatniego dnia biezacego miesiaca. " << endl;
        enteredStartDate = AuxiliaryMethods::readLine();
        if (dateMethods.checkFormatDateIsCorrect(enteredStartDate) == false)
            cout << "Niepoprawny format daty lub niepoprawnie podany zakres czasowy." << endl;

    } while(dateMethods.checkFormatDateIsCorrect(enteredStartDate) == false);

    do {
        cout << "Wprowadz date w formacie rrrr-mm-dd na ktorej chcesz zakonczyc bilans. " << endl;
        cout << "Data musi miescic sie w zakresie czasowym od 2000-01-01 do maksymalnie ostatniego dnia biezacego miesiaca. " << endl;
        enteredEndDate = AuxiliaryMethods::readLine();
        if (dateMethods.checkFormatDateIsCorrect(enteredEndDate) == false)
            cout << endl;
        cout << "Niepoprawny format daty lub niepoprawnie podany zakres czasowy." << endl;


    } while(dateMethods.checkFormatDateIsCorrect(enteredEndDate) == false);

    displayCalculateBalanceSheet(AuxiliaryMethods::convertStringToInt(DateMethods::changeDateWithHyphenToDateWithoutHyphen(enteredStartDate)), AuxiliaryMethods::convertStringToInt(DateMethods::changeDateWithHyphenToDateWithoutHyphen(enteredEndDate)));
    system("pause");

}
