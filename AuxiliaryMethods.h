#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class AuxiliaryMethods
{

public:

    static string readLine();
    static char getchar();
    static int convertStringToInt(const string& number);
    static string convertIntToString(int number);
    static string validateInput (string input);
    static double convertStringToDouble(const string& amount);
};

#endif
