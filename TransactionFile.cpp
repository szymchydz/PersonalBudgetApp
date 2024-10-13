#include "TransactionFile.h"

void TransactionFile::loadCurrentId() {

    if (xmlTransactions.Load(getFileName())) {
        for (const string& elemName : {
                    "Incomes", "Expenses"
                }) {
            if (xmlTransactions.FindElem(elemName)) {
                xmlTransactions.IntoElem();
                while (xmlTransactions.FindElem("Transaction")) {
                    xmlTransactions.IntoElem();
                    if (xmlTransactions.FindElem("TransactionId")) {
                        string elemValue = xmlTransactions.GetElemContent();
                        try {
                            int id = stoi(elemValue);
                            if (id > currentTransactionId) {
                                currentTransactionId = id;
                            }
                        } catch (const exception& e) {
                            cerr << "Invalid TransactionId encountered: " << e.what() << endl;
                        }
                    }
                    xmlTransactions.OutOfElem();
                }
                xmlTransactions.OutOfElem();
            }
        }
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
        cout << "Wczytano istniejący plik XML." << endl;
    }

    if (!xmlTransactions.FindElem("Transactions")) {
        xmlTransactions.AddElem("Transactions");
        cout << "Dodano sekcję Transactions." << endl;
    }

    xmlTransactions.FindElem("Transactions");

    string transactionType;

    if (type == INCOME) {
        transactionType = "Incomes";
    } else if (type == EXPENSE) {
        transactionType = "Expenses";
    } else {
        cout << "Nieznany typ transakcji." << endl;
        return false;
    }

    if (!xmlTransactions.FindElem(transactionType)) {
        xmlTransactions.AddElem(transactionType);
        cout << "Dodano sekcję: " << transactionType << endl;
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
        cout << "Dane zostały zapisane." << endl;
        currentTransactionId++;
        return true;
    } else {
        cout << "Nie udało się zapisać pliku." << endl;
        return false;
    }
}

vector<Transaction> TransactionFile::loadTransactionFromFile(int loggedInUserId) {

    Transaction transaction;
    vector<Transaction> transactions;

    bool fileExists = xmlTransactions.Load(getFileName());

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();

        for (const string& elemName : {
                    "Incomes", "Expenses"
                }) {
            if (xmlTransactions.FindElem(elemName)) {
                xmlTransactions.IntoElem();

                if (xmlTransactions.FindElem("UserId_" + to_string(loggedInUserId))) {
                    xmlTransactions.IntoElem();

                    while (xmlTransactions.FindElem("Transaction")) {
                        xmlTransactions.IntoElem();

                        xmlTransactions.FindChildElem("TransactionId");
                        transaction.id = atoi(xmlTransactions.GetChildData().c_str());

                        xmlTransactions.FindChildElem("UserId");
                        transaction.userId = atoi(xmlTransactions.GetChildData().c_str());

                        xmlTransactions.FindChildElem("Date");
                        transaction.date = atoi(xmlTransactions.GetChildData().c_str());

                        xmlTransactions.FindChildElem("Item");
                        transaction.item = xmlTransactions.GetChildData();

                        xmlTransactions.FindChildElem("Amount");
                        transaction.amount = atof(xmlTransactions.GetChildData().c_str());

                        transactions.push_back(transaction);

                        xmlTransactions.OutOfElem();
                    }
                    xmlTransactions.OutOfElem();
                }
                xmlTransactions.OutOfElem();
            }
        }
    } else {
        cout << "Nie mozna otworzyc pliku." << endl;
    }

    return transactions;
}

/*vector <Transaction> TransactionFile ::loadTransactionFromFile(int loggedInUserId) {

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
}*/
