#ifndef USERSFILE_H
#define USERSFILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

#include "User.h"
#include "AuxiliaryMethods.h"
#include "TextFile.h"

using namespace std;

class UsersFile : public TextFile
{
    CMarkup xmlUsers;

    public:
        UsersFile(const string& fileName) : TextFile (fileName) {};
        bool addUserToFile (User &user);
        vector <User> loadUsersFromFile();
        bool saveChangedPassword(int id, const string &password);

};

#endif // USERSFILE_H
