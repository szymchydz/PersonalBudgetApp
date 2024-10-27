#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdio>
#include <clocale>
#include <string>
#include <algorithm>

#include "AuxiliaryMethods.h"

using namespace std;

class DateMethods
{

public:

    string getTimeFromSystem();
    string getPreviousMonthFromDate(string currentDate);
    int checkNumberOfDaysPerMonth(int currentYear, int currentMonth);
    int getYearFromDate(string date);
    int getMonthFromDate(string date);
    int getDayFromDate(string date);
    bool checkFormatDateIsCorrect(string date);
    static string changeDateWithHyphenToDateWithoutHyphen(string date);
    static string changeDateWithoutHyphenToDateWithHyphen(string date);
    void displayDate(string displayedDate);
};

#endif // DATEMETHODS_H
