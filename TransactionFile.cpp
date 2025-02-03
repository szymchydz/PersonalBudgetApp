#include "TransactionFile.h"

int TransactionFile::loadLastTransactionId() {
 string fileName = getFileName();
 ifstream file(fileName);

     xmlTransactions.Load(fileName);
    if(xmlTransactions.FindElem("Incomes"))
    {
        xmlTransactions.IntoElem();
        while(xmlTransactions.FindChildElem("Transation"))
        {
            while(xmlTransactions.FindChildElem("TransactionId"))
            {
                lastTransactionId = AuxiliaryMethods::convertStringToInt(xmlTransactions.GetChildData());
            }
            xmlTransactions.OutOfElem();
        }
        xmlTransactions.OutOfElem();
    }
    return lastTransactionId;
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
        lastTransactionId = loadLastTransactionId();
        lastTransactionId++;
        return true;
    } else {
        cout << "Nie udalo sie zapisac pliku." << endl;
        return false;
    }
}


vector<Transaction> TransactionFile::loadTransactionsFromFile(int loggedInUserId, const string &transactionType, const string &fileName) {
    Transaction transaction;
    vector<Transaction> transactions;

    if (xmlTransactions.Load(fileName)) {
        if (xmlTransactions.FindElem(transactionType)) {
            xmlTransactions.IntoElem();
            while (xmlTransactions.FindElem("Transaction")) {
                xmlTransactions.FindChildElem("UserId");
                transaction.userId = stoi(xmlTransactions.GetChildData());
                xmlTransactions.FindChildElem("TransactionId");
                transaction.id = stoi(xmlTransactions.GetChildData());
                xmlTransactions.FindChildElem("Date");
                transaction.date = stoi(xmlTransactions.GetChildData());
                xmlTransactions.FindChildElem("Item");
                transaction.item = xmlTransactions.GetChildData();
                xmlTransactions.FindChildElem("Amount");
                transaction.amount = stof(xmlTransactions.GetChildData());
                if (transaction.userId == loggedInUserId)
                    transactions.push_back(transaction);
            }
            xmlTransactions.OutOfElem();
        }
    }
    return transactions;
}

vector<Transaction> TransactionFile::loadIncomesFromFile(int loggedInUserId, string fileNameWithIncomes) {
    return loadTransactionsFromFile(loggedInUserId, "Incomes", fileNameWithIncomes);
}

vector<Transaction> TransactionFile::loadExpensesFromFile(int loggedInUserId, string fileNameWithExpenses) {
    return loadTransactionsFromFile(loggedInUserId, "Expenses", fileNameWithExpenses);
}
