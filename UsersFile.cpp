#include "UsersFile.h"

bool UsersFile :: addUserToFile(User &user) {

    bool fileExists = xmlUsers.Load(getFileName());

    if (!fileExists) {

        xmlUsers.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xmlUsers.AddElem("Users");
    }

    xmlUsers.FindElem();
    xmlUsers.IntoElem();
    xmlUsers.AddElem("User");
    xmlUsers.IntoElem();
    xmlUsers.AddElem("UserId", user.id);
    xmlUsers.AddElem("Name", user.name);
    xmlUsers.AddElem("Surname",user.surname);
    xmlUsers.AddElem("Login", user.login);
    xmlUsers.AddElem("Password", user.password);
    xmlUsers.OutOfElem();

    if (xmlUsers.Save(getFileName())) {
        cout << "Dane zostaly zapisane." << endl;
        return true;
    } else {
        cout << "Nie udalo sie zapisac danych." << endl;
        return false;
    }
}

vector <User> UsersFile::loadUsersFromFile() {

    User user;
    vector <User> users;

    bool fileExists = xmlUsers.Load(getFileName());

    if (fileExists) {
        xmlUsers.ResetPos();
        xmlUsers.FindElem();
        xmlUsers.IntoElem();

        while (xmlUsers.FindElem("User")) {
            xmlUsers.FindChildElem("UserId");
            user.id = atoi(xmlUsers.GetChildData().c_str());

            xmlUsers.FindChildElem("Name");
            user.name = xmlUsers.GetChildData();

            xmlUsers.FindChildElem("Surname");
            user.surname = xmlUsers.GetChildData();

            xmlUsers.FindChildElem("Login");
           user.login = xmlUsers.GetChildData();

            xmlUsers.FindChildElem("Password");
            user.password = xmlUsers.GetChildData();


            users.push_back(user);
        }
        xmlUsers.OutOfElem();
    } else
        cout << "Nie mozna otworzyc pliku." << endl;

    return users;
}

bool UsersFile::saveChangedPassword(int id, const string &password) {

    bool fileExists = xmlUsers.Load(getFileName());

    if (fileExists) {
        xmlUsers.ResetPos();
        xmlUsers.FindElem();
        xmlUsers.IntoElem();
        while (xmlUsers.FindElem("User")) {
            xmlUsers.FindChildElem("UserId");
            int userId = atoi( MCD_2PCSZ(xmlUsers.GetChildData()));
            if (userId == id) {
                xmlUsers.FindChildElem("Password");
                xmlUsers.SetChildData(password);
            }
        }
        if (xmlUsers.Save(getFileName())) {
            cout << "Nowe haslo zostalo zapisane." << endl;
            return true;
        } else {
            cout << "Nie udalo sie zapisac hasla." << endl;
            return false;
        }
        xmlUsers.OutOfElem();
    }
}
