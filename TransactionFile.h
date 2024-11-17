#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H

#include <iostream>
#include <vector>
#include "Transaction.h"
#include "TextFile.h"
#include "Type.h"

class TransactionFile : public TextFile {
    CMarkup xmlTransactions;
    int currentTransactionId;

public:
    TransactionFile(const string& fileName) : TextFile(fileName), currentTransactionId(0) {}

    int getCurrentTransactionId() const { return currentTransactionId; }
    void loadCurrentId();
    bool addTransactionToFile(Transaction &transaction, const Type &type);
    vector<Transaction> loadTransactionFromFile(int loggedInUserId, Type type);
};

#endif // TRANSACTIONFILE_H

