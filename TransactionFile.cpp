#include "TransactionFile.h"

void TransactionFile::loadCurrentId() {

    if (xmlTransactions.Load(getFileName())) {
        for (const string& elemName : {"Incomes", "Expenses"}) {
            if (xmlTransactions.FindElem(elemName)) {
                xmlTransactions.IntoElem();
                while (xmlTransactions.FindElem("Transaction")) {
                    xmlTransactions.IntoElem();
                    if (xmlTransactions.FindElem("TransactionId")) {
                        string elemValue = xmlTransactions.GetElemContent();
                        try {
                            int id = stoi(elemValue); // Convert string to int
                            if (id > currentTransactionId) {
                                currentTransactionId = id; // Update if id is greater
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
    cout << "Sprawdzam plik: " << fileName << std::endl;

    // Sprawdzamy, czy plik istnieje
    ifstream file(fileName);
    bool fileExists = file.good();
    file.close(); // Zamknij plik po sprawdzeniu

    if (!fileExists) {
        // Tworzymy nowy dokument XML, jeśli plik nie istnieje
        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<Transactions></Transactions>");
        cout << "Utworzono nowy plik XML." << endl;
    } else {
        cout << "Wczytano istniejący plik XML." << endl;
    }

    // Znajdujemy sekcję główną "Transactions"
    if (!xmlTransactions.FindElem("Transactions")) {
        xmlTransactions.AddElem("Transactions");
        cout << "Dodano sekcję Transactions." << endl;
    }

    xmlTransactions.FindElem("Transactions"); // Wchodzimy do sekcji Transactions

    std::string transactionType;

    // Ustal typ transakcji
    if (type == INCOME) {
        transactionType = "Incomes";
    } else if (type == EXPENSE) {
        transactionType = "Expenses";
    } else {
        cout << "Nieznany typ transakcji." << endl;
        return false;
    }

    // Znajdź lub dodaj sekcję Incomes/Expenses
    if (!xmlTransactions.FindElem(transactionType)) {
        xmlTransactions.AddElem(transactionType);
        cout << "Dodano sekcję: " << transactionType << endl;
    }

    // Wchodzimy do sekcji (Incomes lub Expenses)
    xmlTransactions.IntoElem();

    // Dodajemy nową transakcję na końcu sekcji
    xmlTransactions.AddElem("Transaction");
    xmlTransactions.IntoElem();  // Wejdź do nowo dodanego elementu "Transaction"
    xmlTransactions.AddElem("TransactionId", transaction.id);
    xmlTransactions.AddElem("UserId", transaction.userId);  // Dodajemy UserId
    xmlTransactions.AddElem("Date", transaction.date);
    xmlTransactions.AddElem("Item", transaction.item);
    xmlTransactions.AddElem("Amount", transaction.amount);
    xmlTransactions.OutOfElem();  // Wychodzimy z "Transaction"
    xmlTransactions.OutOfElem();  // Wychodzimy z sekcji (Incomes/Expenses)

    // Zapisz zmiany w pliku
    if (xmlTransactions.Save(getFileName())) {
        cout << "Dane zostały zapisane." << endl;
        currentTransactionId++;  // Zwiększ ID dla nowej transakcji
        return true;
    } else {
        cout << "Nie udało się zapisać pliku." << endl;
        return false;
    }
}
/*bool TransactionFile::addTransactionToFile(Transaction &transaction, const Type &type) {

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
        cout << "Nie udalo sie zapisac danych." << endl;
        return false;
    }
}*/

vector<Transaction> TransactionFile::loadTransactionFromFile(int loggedInUserId) {

    Transaction transaction;
    vector<Transaction> transactions;

    bool fileExists = xmlTransactions.Load(getFileName());

    if (fileExists) {
        xmlTransactions.ResetPos();
        xmlTransactions.FindElem();  // Root element <Transactions>

        // Load both Incomes and Expenses for the specific user
        for (const string& elemName : {"Incomes", "Expenses"}) {
            if (xmlTransactions.FindElem(elemName)) {
                xmlTransactions.IntoElem();

                // Now find the specific section for the loggedInUserId
                if (xmlTransactions.FindElem("UserId_" + to_string(loggedInUserId))) {
                    xmlTransactions.IntoElem();

                    // Iterate through all transactions for this user
                    while (xmlTransactions.FindElem("Transaction")) {
                        xmlTransactions.IntoElem();  // Enter the <Transaction> element

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

                        xmlTransactions.OutOfElem();  // Exit the <Transaction> element
                    }
                    xmlTransactions.OutOfElem();  // Exit UserId section
                }
                xmlTransactions.OutOfElem();  // Exit Incomes/Expenses
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
