#include "TransactionFile.h"


void TransactionFile::loadCurrentId() {
    vector<Transaction> incomeTransactions = loadTransactionFromFile(-1, INCOME);
    vector<Transaction> expenseTransactions = loadTransactionFromFile(-1, EXPENSE);

    int maxIncomeId = incomeTransactions.empty() ? 0 : incomeTransactions.back().id;
    int maxExpenseId = expenseTransactions.empty() ? 0 : expenseTransactions.back().id;

    currentTransactionId = max(maxIncomeId, maxExpenseId);
}


vector<Transaction> TransactionFile::loadTransactionFromFile(int loggedInUserId, Type type) {
    vector<Transaction> transactions;
    bool fileExists = xmlTransactions.Load(getFileName());

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();


        string transactionType = (type == INCOME) ? "Incomes" : "Expenses";
        while (xmlTransactions.FindElem(transactionType)) {
            xmlTransactions.IntoElem();
            while (xmlTransactions.FindElem("Transaction")) {
                xmlTransactions.IntoElem();
                xmlTransactions.FindChildElem("UserId");
                int userId = atoi(xmlTransactions.GetChildData().c_str());

                if (userId == loggedInUserId) {
                    Transaction transaction;
                    transaction.userId = userId;
                    xmlTransactions.FindChildElem("TransactionId");
                    transaction.id = atoi(xmlTransactions.GetChildData().c_str());
                    xmlTransactions.FindChildElem("Date");
                    transaction.date = atoi(xmlTransactions.GetChildData().c_str());
                    xmlTransactions.FindChildElem("Item");
                    transaction.item = xmlTransactions.GetChildData();
                    xmlTransactions.FindChildElem("Amount");
                    transaction.amount = atof(xmlTransactions.GetChildData().c_str());

                    transactions.push_back(transaction);
                }
                xmlTransactions.OutOfElem();
            }
            xmlTransactions.OutOfElem();
        }
    } else {
        cout << "Nie mozna otworzyc pliku: " << getFileName() << endl;
    }
    return transactions;
}

bool TransactionFile::addTransactionToFile(Transaction &transaction, const Type &type) {
    string fileName = getFileName();
    ifstream file(fileName);
    bool fileExists = file.good();
    file.close();

    if (!fileExists) {
        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<Transactions></Transactions>");
        cout << "Utworzono nowy plik XML." << endl;
    } else {
        xmlTransactions.Load(fileName);
        cout << "Wczytano istniejacy plik XML." << endl;
    }

    if (!xmlTransactions.FindElem("Transactions")) {
        xmlTransactions.AddElem("Transactions");
    }
    xmlTransactions.IntoElem();

    string transactionType = (type == INCOME) ? "Incomes" : "Expenses";
    if (!xmlTransactions.FindElem(transactionType)) {
        xmlTransactions.AddElem(transactionType);
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
        cout << "Nie udało się zapisac pliku." << endl;
        return false;
    }
}

