#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H


#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <filesystem>

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
    TransactionFile(const string& fileName) : TextFile(fileName) {
        lastTransactionId = 0;
    };
    int lastTransactionId = 0;
    bool addTransactionToFile(const Transaction &transaction, const Type &type);
    vector<Transaction> loadTransactionsFromFile(int loggedInUserId, const string &transactionType, const string &fileName);
    vector<Transaction> loadIncomesFromFile(int loggedInUserId, string fileName);
    vector<Transaction> loadExpensesFromFile(int loggedInUserId, string fileName);
    int loadLastTransactionId();

};

#endif // TRANSACTIONFILE_H
