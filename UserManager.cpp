#include "UserManager.h"




void UserManager :: addUser() {

    User user = enterUserData();

    users.push_back(user);
    usersFile.addUserToFile(user);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
    cin.ignore();

}

int UserManager :: getLastUserId() {
    if (users.empty() == true)
        return 1;
    else
        return users.back().id + 1;
}

User UserManager :: enterUserData() {

    User user;

    user.id = getLastUserId();

    do {
        string name;
        cout << "Podaj imie: ";
        user.name = AuxiliaryMethods :: readLine();

        string surname;
        cout << "Podaj nazwisko: ";
        user.surname = AuxiliaryMethods :: readLine();

        string login;
        cout << "Podaj login: ";
        user.login = AuxiliaryMethods :: readLine();

    } while (checkIfLoginExist(user.login) == true);

    string password;
    cout << "Podaj haslo: ";
    user.password = AuxiliaryMethods :: readLine();

    return user;
}


bool UserManager :: checkIfLoginExist(const string &login) {

    for (int i = 0; i < users.size(); i++) {
        if (users[i].login == login) {
            cout << endl << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }
        return false;
    }
}

int UserManager :: loginUser() {

    string login = "", password = "";

    cout << endl << "Podaj login: ";
    login = AuxiliaryMethods :: readLine();

    for (int  i = 0; i < users.size(); i++) {
        if (users[i].login == login) {
            for (int attemptQuantity = 3; attemptQuantity > 0; attemptQuantity--) {
                cout << "Podaj haslo. Pozostalo prob: " << attemptQuantity << ": ";
                password = AuxiliaryMethods :: readLine();

                if (users[i].password== password) {
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    loggedInUserId = users[i].id;
                    return loggedInUserId;
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl << endl;
    system("pause");
    return 0;
}

bool UserManager :: isUserLoggedIn() {
    return (loggedInUserId > 0) ? true : false;
}

void UserManager::logoutUser() {
    loggedInUserId = 0;
}

int UserManager::getLoggedInUserId() {
    return loggedInUserId;
}

void UserManager :: changeUserPassword() {
    string newPassword = "";
    cout << "Podaj nowe haslo: ";
    newPassword = AuxiliaryMethods :: readLine();

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++) {
        if (itr -> id == loggedInUserId) {
            itr -> password = newPassword;
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    /*  usersFile.
      plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);*/
}
