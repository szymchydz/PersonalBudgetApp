/*#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H


#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

#include "Transaction.h"
#include "AuxiliaryMethods.h"
#include "TextFile.h"

using namespace std;

class TransactionFile : public TextFile
{
    CMarkup xmlTransactions;

    public:
        TransactionsFile(const string& fileName) : TextFile (fileName) {};
        bool addTransactionToFile (Transaction &transaction);
        vector <Transaction> loadTransactionFromFile();:
};

#endif // TRANSACTIONFILE_H
*/
