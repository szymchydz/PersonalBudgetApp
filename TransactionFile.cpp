/*#include "TransactionFile.h"

bool TransactionFile :: addTransactionToFile(User &user) {

    bool fileExists = xmlTransactions.Load(getFileName());

    if (!fileExists) {

        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");

       switch(type) {
        case INCOME:
            xml.AddElem("Incomes");
            break;
        case EXPENSE:
            xml.AddElem("Expenses");
            break;
        }
    }

    xmlTransactions.FindElem();
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("Transaction");
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("Transactiond", transaction.id);
    xmlTransactions.AddElem("Date", transaction.date);
    xmlTransactions.AddElem("Surname",user.surname);
    xmlTransactions.AddElem("Login", user.login);
    xmlTransactions.AddElem("Password", user.password);
    xmlTransactions.OutOfElem();

    if (xmlTransactions.Save(getFileName())) {
        cout << "Dane zostaly zapisane." << endl;
        return true;
    } else {
        cout << "Nie udalo sie zapisac danych." << endl;
        return false;
    }*/
