#include "TransactionFile.h"

void TransactionFile::loadCurrentId() {
    string transactionFile;

    vector<Transaction> transactions = loadTransactionFromFiles(-1, transactionFile);
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
        if (!xmlTransactions.Load(fileName)) {
            cout << "Blad podczas wczytywania istniejacego pliku XML." << endl;
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


vector<Transaction> TransactionFile::loadTransactionFromFiles(int loggedInUserId, string fileNameWithIncomes) {
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

/*fileExists = xmlTransactions.Load(expensesFileName);
if (fileExists) {
    xmlTransactions.ResetPos();
    xmlTransactions.FindElem();
    while (xmlTransactions.FindElem("Expenses")) {
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
    cout << "Nie mozna otworzyc pliku wydatkow." << endl;
}

return transactions;
}*/
