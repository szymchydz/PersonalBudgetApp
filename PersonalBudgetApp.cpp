#include "PersonalBudgetApp.h"


void PersonalBudgetApp :: registerNewUser() {
    userManager.addUser();
}


void PersonalBudgetApp :: loginUser() {
    userManager.loginUser();
}


void PersonalBudgetApp :: changeUserPassword() {
    userManager.changeUserPassword();
}
