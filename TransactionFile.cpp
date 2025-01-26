#include "TransactionFile.h"

void TransactionFile::loadCurrentId() {
    string fileName = getFileName();
    vector<Transaction> incomes = loadIncomesFromFile(-1, fileName);
    vector<Transaction> expenses = loadExpensesFromFile(-1, fileName);

    int maxIncomeId = 0;
    int maxExpenseId = 0;

    if (!incomes.empty()) {
        maxIncomeId = max_element(
            incomes.begin(), incomes.end(),
            [](const Transaction &a, const Transaction &b) { return a.id < b.id; }
        )->id;
    }

    if (!expenses.empty()) {
        maxExpenseId = max_element(
            expenses.begin(), expenses.end(),
            [](const Transaction &a, const Transaction &b) { return a.id < b.id; }
        )->id;
    }

    currentTransactionId = max(maxIncomeId, maxExpenseId);
}

bool TransactionFile::addTransactionToFile(const Transaction &transaction, const Type &type) {
    string fileName = getFileName();
    ifstream file(fileName);
    bool fileExists = file.good();
    file.close();

    if (!fileExists) {
        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        cout << "Utworzono nowy plik XML." << endl;
    } else {
        if (!xmlTransactions.Load(fileName)) {
            cerr << "Blad podczas wczytywania istniejacego pliku XML." << endl;
            return false;
        }
        cout << "Wczytano istniejacy plik XML." << endl;
    }

    string transactionType = (type == INCOME) ? "Incomes" : "Expenses";
    if (!xmlTransactions.FindElem(transactionType)) {
        xmlTransactions.AddElem(transactionType);
        cout << "Dodano sekcje: " << transactionType << endl;
    }
    xmlTransactions.IntoElem();

    xmlTransactions.AddElem("Transaction");
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("TransactionId", transaction.id);
    xmlTransactions.AddElem("UserId", transaction.userId);
    xmlTransactions.AddElem("Date", transaction.date);
    xmlTransactions.AddElem("Item", transaction.item);
    xmlTransactions.AddElem("Amount", transaction.amount);
    xmlTransactions.OutOfElem();
    xmlTransactions.OutOfElem();
    xmlTransactions.OutOfElem();

    if (xmlTransactions.Save(fileName)) {
        cout << "Dane zostaly zapisane." << endl;
        currentTransactionId++;
        return true;
    } else {
        cout << "Nie udalo sie zapisac pliku." << endl;
        return false;
    }
}


vector<Transaction> TransactionFile::loadIncomesFromFile(int loggedInUserId, string fileNameWithIncomes) {
    Transaction income;
    vector<Transaction> incomes;

    bool fileExists = xmlTransactions.Load(fileNameWithIncomes);


    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem("Incomes");
        xmlTransactions.IntoElem();

            while (xmlTransactions.FindElem("Transaction")) {

                xmlTransactions.FindChildElem("UserId");
                income.userId = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("TransactionId");
                income.id = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("Date");
                income.date = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("Item");
                income.item = xmlTransactions.GetChildData();

                xmlTransactions.FindChildElem("Amount");
                income.amount = atof(xmlTransactions.GetChildData().c_str());

                if (income.userId == loggedInUserId)
                    incomes.push_back(income);
            }

            xmlTransactions.OutOfElem();
        }
    return incomes;
}

vector<Transaction> TransactionFile::loadExpensesFromFile(int loggedInUserId, string fileNameWithExpenses) {
    Transaction expense;
    vector<Transaction> expenses;

    bool fileExists = xmlTransactions.Load(fileNameWithExpenses);


    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem("Expenses");
        xmlTransactions.IntoElem();

            while (xmlTransactions.FindElem("Transaction")) {

                xmlTransactions.FindChildElem("UserId");
                expense.userId = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("TransactionId");
                expense.id = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("Date");
                expense.date = atoi(xmlTransactions.GetChildData().c_str());

                xmlTransactions.FindChildElem("Item");
                expense.item = xmlTransactions.GetChildData();

                xmlTransactions.FindChildElem("Amount");
                expense.amount = atof(xmlTransactions.GetChildData().c_str());

                if (expense.userId == loggedInUserId)
                    expenses.push_back(expense);
            }

            xmlTransactions.OutOfElem();
        }
    return expenses;
}


