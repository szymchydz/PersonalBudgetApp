#include "UserManager.h"

void UserManager :: registerUser() {

    User user = enterUserData();

    users.push_back(user);
    //userFile.dopiszUzytkownikaDoPliku(user);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
    cin.ignore();

}

User UserManager :: enterUserData() {

    User user;

    user.id(pobierzIdNowegoUzytkownika());

    string name;
    do {
        cout << "Podaj imie: ";
        cin >> name;

        user.name;
    }

    string surname;
    do {
        cout << "Podaj imie: ";
        cin >> surname;

        user.surname;
    }

    string login;
    do {
        cout << "Podaj login: ";
        cin >> login;

        user.login;
    }

    while (checkIfLoginExist(user.login) == true);

    string password;

    cout << "Podaj haslo: ";
    cin >> password;
    uzytkownik.password;

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

    for (int  i = 0; i < users.size(); i++){
        if (users[i].login == login) {
            for (int attemptQuantity = 3; attemptQuantity > 0; attemptQuantity--) {
                cout << "Podaj haslo. Pozostalo prob: " << attemptQuantity << ": ";
                password = AuxiliaryMethods :: readLine();

                if (users[i].password== password) {
                    cout << endl << "Zalogowales sie." << endl << endl;
                    system("pause");
                    loggedInUserId = uzytkownicy[i].id;
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

bool UserManager :: isUserLoggedIn(){
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
        if (itr -> user.id == loggedInUserId) {
            itr -> user.password = newPassword;
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    /*userFile.
    plikZUzytkownikami.zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);*/
}
