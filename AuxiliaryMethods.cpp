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

int AuxiliaryMethods::convertStringToInt(string number) {

    int numberInt;
    istringstream iss(number);
    iss >> numberInt;

    return numberInt;

}

string AuxiliaryMethods :: validateInput (string input) {

int sizeOfAmount = input.size();

    for (int i = 0; i < sizeOfAmount; i++) {

        if ((input[i] == ',') ||(input[i]=='.')) {
            input[i] = '.';
            if (sizeOfAmount > i+3)
                input.erase(i+3, sizeOfAmount-i-3);
            return input;
        }
    }

    return input;
}

string AuxiliaryMethods::convertIntToString(int number) {

    ostringstream ss;
    ss << number;
    string str = ss.str();

    return str;
}

double AuxiliaryMethods::convertStringToDouble(string amount) {

    double amountDouble = atof(amount.c_str());

    return amountDouble;
}
