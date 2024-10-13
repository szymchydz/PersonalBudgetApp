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

    string getTimeFromSystem(const std::string& format = "%Y-%m-%d %H:%M:%S");
    string getPreviousMonthFromDate(string currentDate);
    int checkNumberOfDaysPerMonth(int currentYear, int currentMonth);
    int getYearFromDate(string date);
    int getMonthFromDate(string date);
    int getDayFromDate(string date);
    bool checkFormatDateIsCorrect(string date);
    static string changeDateWithHypenToDateWithoutHyphen(string date);
    static string changeDateWithoutHypenToDateWithHyphen(string date);
    void displayDate(string displayedDate);
    static string getEndDate(const string& currentDate);
    static string getStartDate(const string& currentDate);
};

#endif // DATEMETHODS_H
