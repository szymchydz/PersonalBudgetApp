#include "TransactionFile.h"

bool TransactionFile :: addTransactionToFile (Transaction &transaction, const Type &type) {

    bool fileExists = xmlTransactions.Load(getFileName());

    if (!fileExists) {

        xmlTransactions.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");

       switch(type) {
        case INCOME:
            xmlTransactions.AddElem("Incomes");
            break;
        case EXPENSE:
            xmlTransactions.AddElem("Expenses");
            break;
        }
    }

    xmlTransactions.FindElem();
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("Transaction");
    xmlTransactions.IntoElem();
    xmlTransactions.AddElem("TransactionId", transaction.id);
    xmlTransactions.AddElem("UserId", transaction.userId);
    xmlTransactions.AddElem("Date", transaction.date);
    xmlTransactions.AddElem("Item",transaction.item);
    xmlTransactions.AddElem("Amount", transaction.amount);
    xmlTransactions.OutOfElem();

    if (xmlTransactions.Save(getFileName())) {
        cout << "Dane zostaly zapisane." << endl;
        return true;
    } else {
        cout << "Nie udalo sie zapisac danych." << endl;
        return false;
    }
}
