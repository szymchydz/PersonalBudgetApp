#include "AuxiliaryMethods.h"

char AuxiliaryMethods :: getchar() {
    string input = "";
    char sign  = {0};

    while (true) {
        getline(cin, input);

        if (input.length() == 1) {
            sign = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

string AuxiliaryMethods :: readLine() {
    string input = "";
    getline(cin, input);
    return input;
}

bool AuxiliaryMethods :: validateInput (string input) {





}
