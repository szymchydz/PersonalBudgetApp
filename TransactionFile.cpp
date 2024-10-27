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
        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        cout << "Utworzono nowy plik XML." << endl;
    } else {
        cout << "Wczytano istniejacy plik XML." << endl;
    }

    xmlTransactions.FindElem("Transactions");

    string transactionType = (type == INCOME) ? "Incomes" : "Expenses";

    if (!xmlTransactions.FindElem(transactionType)) {
        xmlTransactions.AddElem(transactionType);
        cout << "Dodano sekcje: " << transactionType << endl;
    }

    xmlTransactions.IntoElem();
    xmlTransactions.FindElem(transactionType);
    xmlTransactions.AddElem("Transaction");
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("TransactionId", transaction.id);
    xmlTransactions.AddElem("UserId", transaction.userId);
    xmlTransactions.AddElem("Date", transaction.date);
    xmlTransactions.AddElem("Item", transaction.item);
    xmlTransactions.AddElem("Amount", transaction.amount);
    xmlTransactions.OutOfElem();
    xmlTransactions.OutOfElem();

    if (xmlTransactions.Save(getFileName())) {
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
    cout << getFileName() << endl;
    system("pause");

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();

        cout << "Zaladowano plik XML pomyślnie." << endl;

        for (const string& elemName : {
                    "Incomes", "Expenses"
                }) {
            if (xmlTransactions.FindElem(elemName)) {
                xmlTransactions.IntoElem();

                while (xmlTransactions.FindElem("Transaction")) {
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
                        cout << "Dodano transakcje ID: " << transaction.id << endl;
                    } else {
                        cout << "Pominieto transakcje, poniewaz UserId sie nie zgadza." << endl;
                    }

                    xmlTransactions.OutOfElem();
                }
                xmlTransactions.OutOfElem();
            } else {
                cout << "Nie znaleziono sekcji: " << elemName << endl;
            }
        }
    } else {
        cout << "Nie mozna otworzyc pliku." << endl;
    }

    cout << "Liczba zaladowanych transakcji: " << transactions.size() << endl;
    system("pause");
    return transactions;
}



