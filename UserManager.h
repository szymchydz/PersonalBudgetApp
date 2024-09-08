#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "User.h"
#include "UsersFile.h"

using namespace std;

class UserManager {

    int loggedInUserId;
    vector <User> users;
    UsersFile usersFile;

    bool checkIfLoginExist(const string &login);
    User enterUserData();
    int getLastUserId();

public:
    UserManager(string usersFileName) : usersFile (usersFileName) {
        loggedInUserId = 0;
        users = usersFile.loadUsersFromFile();
    };


    void addUser();
    int loginUser();
    void changeUserPassword();
    void logoutUser();

    bool isUserLoggedIn();
    int getLoggedInUserId();

};

#endif
