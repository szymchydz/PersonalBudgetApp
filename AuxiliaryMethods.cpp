#include "AuxiliaryMethods.h"

char AuxiliaryMethods::getchar() {
    string input;
    while (true) {
        getline(cin, input);

        if (input.length() == 1) {
            return input[0];
        }
        cout << "To nie jest pojedynczy znak. Sprobuj ponownie." << endl;
    }
}

string AuxiliaryMethods::readLine() {
    string input;
    getline(cin, input);
    return input;
}

int AuxiliaryMethods::convertStringToInt(const string& number) {
    int numberInt;
    istringstream(number) >> numberInt;
    return numberInt;
}

string AuxiliaryMethods::validateInput(string input) {
    size_t sizeOfAmount = input.size();

    for (size_t i = 0; i < sizeOfAmount; i++) {
        if (input[i] == ',' || input[i] == '.') {
            input[i] = '.';

            if (sizeOfAmount > i + 3) {
                input.erase(i + 3, sizeOfAmount - i - 3);
            }
            return input;
        }
    }
    return input;
}

string AuxiliaryMethods::convertIntToString(int number) {
    return to_string(number);
}

double AuxiliaryMethods::convertStringToDouble(const string& amount) {
    return atof(amount.c_str());
}
