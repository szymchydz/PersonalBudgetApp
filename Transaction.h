#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

struct Transaction {
    int id = 0;
    int userId = 0;
    int date = 0;
    string item = "";
    double amount = 0.0;
};

#endif

