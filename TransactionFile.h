#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H


#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

#include "Transaction.h"
#include "AuxiliaryMethods.h"
#include "DateMethods.h"
#include "TextFile.h"
#include "Type.h"
#include "Markup.h"

using namespace std;

class TransactionFile : public TextFile {
    CMarkup xmlTransactions;

public:
    TransactionFile(const string& fileName) : TextFile(fileName), currentTransactionId(0) {
        loadCurrentId();
    };
    int currentTransactionId;
    bool addTransactionToFile (Transaction &transaction, const Type &type);
    vector <Transaction> loadTransactionFromFile(int loggedInUserId);
    void loadCurrentId();

};

#endif // TRANSACTIONFILE_H
