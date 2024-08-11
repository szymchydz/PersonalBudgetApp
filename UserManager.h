#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "User.h"
//#include "UserFile.h"

using namespace std;

class UserManager {

    int loggedInUserId;
    vector <User> users;
    //UserFile userFile;

    bool checkIfLoginExist(const string &login);
    User enterUserData();

public:
    UserManager(string userFilename);


    void registerUser();
    int loginUser();
    void changeUserPassword();
    void logoutUser();

    bool isUserLoggedIn();
    int getLoggedInUserId();

};

#endif
