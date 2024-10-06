#include "TransactionFile.h"

void TransactionFile :: loadCurrentId() {

     if (xmlTransactions.Load(getFileName())) {
            // Sprawdü obecnoúÊ elementÛw "Incomes" i "Expenses"
            for (const string& elemName : {"Incomes", "Expenses"}) {
                if (xmlTransactions.FindElem(elemName)) {
                    xmlTransactions.IntoElem(); // Wejdü do elementu
                    while (xmlTransactions.FindElem("Transaction")) {
                        xmlTransactions.IntoElem(); // Wejdü do "Transaction"
                        if (xmlTransactions.FindElem("TransactionId")) {
                            string elemValue = xmlTransactions.GetElemContent(); // Odczytaj wartoúÊ
                            int id = stoi(elemValue); // ZamieÒ string na int
                            if (id > currentTransactionId) {
                                currentTransactionId = id; // Zaktualizuj bieøπce ID
                            }
                        }
                        xmlTransactions.OutOfElem(); // Wyjdü z "Transaction"
                    }
                    xmlTransactions.OutOfElem(); // Wyjdü z elementu "Incomes" lub "Expenses"
                }
            }
        }
    }

bool TransactionFile::addTransactionToFile(Transaction &transaction, const Type &type) {

    bool fileExists = xmlTransactions.Load(getFileName());

    if (!fileExists) {
        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
    }

    if (type == INCOME) {
        if (!xmlTransactions.FindElem("Incomes")) {
            xmlTransactions.AddElem("Incomes");
        }
        xmlTransactions.FindElem("Incomes");
    } else if (type == EXPENSE) {
        if (!xmlTransactions.FindElem("Expenses")) {
            xmlTransactions.AddElem("Expenses");
        }
        xmlTransactions.FindElem("Expenses");
    } else {
        cout << "Nieznany typ transakcji." << endl;
        return false;
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

    if (xmlTransactions.Save(getFileName())) {
        cout << "Dane zostaly zapisane." << endl;
        currentTransactionId++;
        return true;
    } else {
        cout << "Nie uda≥o siÍ zapisac danych." << endl;
        return false;
    }
}

vector <Transaction> TransactionFile ::loadTransactionFromFile(int loggedInUserId) {

    Transaction transaction;
    vector <Transaction> transactions;

    bool fileExists = xmlTransactions.Load(getFileName());

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();
        xmlTransactions.IntoElem();

        while (xmlTransactions.FindElem("Transaction")) {
            xmlTransactions.FindChildElem("TransactionId");
            transaction.id = atoi(xmlTransactions.GetChildData().c_str());

            xmlTransactions.FindChildElem("UserId");
            transaction.userId = atoi(xmlTransactions.GetChildData().c_str());

            xmlTransactions.FindChildElem("Date");
            transaction.date = atoi(xmlTransactions.GetChildData().c_str());

            xmlTransactions.FindChildElem("Item");
            transaction.item = xmlTransactions.GetChildData();

            xmlTransactions.FindChildElem("Amount");
            transaction.amount = atoi(xmlTransactions.GetChildData().c_str());


            transactions.push_back(transaction);
        }
        xmlTransactions.OutOfElem();
    } else
        cout << "Nie mozna otworzyc pliku." << endl;

    return transactions;
}
