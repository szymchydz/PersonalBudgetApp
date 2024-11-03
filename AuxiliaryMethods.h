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
    static int convertStringToInt(string number);
    static string convertIntToString(int number);
    static string validateInput (string input);
    static double convertStringToDouble(string amount);
};

#endif
