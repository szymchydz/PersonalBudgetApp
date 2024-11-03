#include "TransactionFile.h"

void TransactionFile::loadCurrentId() {
    vector<Transaction> transactions = loadTransactionFromFile(-1);
    if (!transactions.empty()) {
        currentTransactionId = transactions.back().id;
    } else {
        currentTransactionId = 0;
    }
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

vector<Transaction> TransactionFile::loadTransactionFromFile(int loggedInUserId) {

    vector<Transaction> transactions;
    bool fileExists = xmlTransactions.Load(getFileName());

  if (fileExists) {
    xmlTransactions.ResetPos();
    xmlTransactions.FindElem();

    while (xmlTransactions.FindElem("Incomes")) {
        cout << "Znaleziono sekcję Incomes" << endl;
        xmlTransactions.IntoElem();

        while (xmlTransactions.FindElem("Transaction")) {
            cout << "Znaleziono transakcję w Incomes" << endl;
            xmlTransactions.IntoElem();

            xmlTransactions.FindChildElem("UserId");
            int userId = atoi(xmlTransactions.GetChildData().c_str());
            cout << "Znaleziono UserId: " << userId << endl;

            if (userId == loggedInUserId) {
                Transaction transaction;
                if (xmlTransactions.FindChildElem("TransactionId")) {
                    transaction.id = atoi(xmlTransactions.GetChildData().c_str());
                }
                if (xmlTransactions.FindChildElem("Date")) {
                    transaction.date = atoi(xmlTransactions.GetChildData().c_str());
                }
                if (xmlTransactions.FindChildElem("Item")) {
                    transaction.item = xmlTransactions.GetChildData();
                }
                if (xmlTransactions.FindChildElem("Amount")) {
                    transaction.amount = atof(xmlTransactions.GetChildData().c_str());
                }

                transactions.push_back(transaction);
                cout << "Dodano transakcje: " << transaction.item << " w wysokosci " << transaction.amount << endl;
            }

            xmlTransactions.OutOfElem();
        }
        xmlTransactions.OutOfElem();
    }

    while (xmlTransactions.FindElem("Expenses")) {
        cout << "Znaleziono sekcję Expenses" << endl;
        xmlTransactions.IntoElem();

        while (xmlTransactions.FindElem("Transaction")) {
            cout << "Znaleziono transakcję w Expenses" << endl;
            xmlTransactions.IntoElem();

            xmlTransactions.FindChildElem("UserId");
            int userId = atoi(xmlTransactions.GetChildData().c_str());
            cout << "Znaleziono UserId: " << userId << endl;

            if (userId == loggedInUserId) {
                Transaction transaction;
                if (xmlTransactions.FindChildElem("TransactionId")) {
                    transaction.id = atoi(xmlTransactions.GetChildData().c_str());
                }
                if (xmlTransactions.FindChildElem("Date")) {
                    transaction.date = atoi(xmlTransactions.GetChildData().c_str());
                }
                if (xmlTransactions.FindChildElem("Item")) {
                    transaction.item = xmlTransactions.GetChildData();
                }
                if (xmlTransactions.FindChildElem("Amount")) {
                    transaction.amount = atof(xmlTransactions.GetChildData().c_str());
                }

                transactions.push_back(transaction);
                cout << "Dodano transakcję: " << transaction.item << " w wysokości " << transaction.amount << endl;
            }

            xmlTransactions.OutOfElem();
        }
        xmlTransactions.OutOfElem();
    }
} else {
    cout << "Nie mozna otworzyc pliku." << endl;
}
    return transactions;
}



/*vector<Transaction> TransactionFile::loadTransactionFromFile(int loggedInUserId) {

    vector<Transaction> transactions;
    bool fileExists = xmlTransactions.Load(getFileName());

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();

        while (xmlTransactions.FindElem("Incomes") || xmlTransactions.FindElem("Expenses")) {
            string elemName = xmlTransactions.GetTagName();
            xmlTransactions.IntoElem();

            while (xmlTransactions.FindElem("Transaction")) {
                xmlTransactions.IntoElem();

                xmlTransactions.FindChildElem("UserId");
                int userId = atoi(xmlTransactions.GetChildData().c_str());

                if (userId == loggedInUserId) {
                    Transaction transaction;

                    if (xmlTransactions.FindChildElem("TransactionId")) {
                        transaction.id = atoi(xmlTransactions.GetChildData().c_str());
                    }
                    if (xmlTransactions.FindChildElem("Date")) {
                        transaction.date = atoi(xmlTransactions.GetChildData().c_str());
                    }
                    if (xmlTransactions.FindChildElem("Item")) {
                        transaction.item = xmlTransactions.GetChildData();
                    }
                    if (xmlTransactions.FindChildElem("Amount")) {
                        transaction.amount = atof(xmlTransactions.GetChildData().c_str());
                    }

                    transactions.push_back(transaction);
                }

                xmlTransactions.OutOfElem();
            }
            xmlTransactions.OutOfElem();
        }
    } else {
        cout << "Nie mozna otworzyc pliku." << endl;
    }
    return transactions;
}*/


