#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H


#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

#include "Transaction.h"
#include "AuxiliaryMethods.h"
#include "TextFile.h"
#include "Type.h"


using namespace std;

class TransactionFile : public TextFile {
    CMarkup xmlTransactions;

public:
    TransactionFile(const string& fileName) : TextFile (fileName), currentTransactionId(0) {
        loadCurrentId();
    };
    bool addTransactionToFile (Transaction &transaction, const Type &type);
    vector <Transaction> loadTransactionFromFile(int loggedInUserId);
    int currentTransactionId;
    void loadCurrentId();
};

#endif // TRANSACTIONFILE_H

