#include <iostream>

#include "PersonalBudgetApp.h"

using namespace std;

int main() {


    PersonalBudgetApp personalBudgetApp ("users.xml");

    personalBudgetApp.registerNewUser();

    personalBudgetApp.loginUser();

    personalBudgetApp.changeUserPassword();



    return 0;
}



