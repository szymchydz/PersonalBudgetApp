#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

struct User {
    int id = 0;
    string name = "";
    string surname = "";
    string login = "";
    string password = "";
};

#endif

