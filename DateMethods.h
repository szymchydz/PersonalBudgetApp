#ifndef DATEMETHODS_H
#define DATEMETHODS_H

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
    int checkNumberOfDaysPerMonth(int currentYear, int currentMonth);
    bool checkFormatDateIsCorrect(const string& date);
    static string changeDateWithHyphenToDateWithoutHyphen(const string& date);
    static string changeDateWithoutHyphenToDateWithHyphen(const string& date);
    void displayDate(const string& displayedDate);
    int getYearFromDate(const string& date);
    int getMonthFromDate(const string& date);
    string getPreviousMonthFromDate(const string& currentDate);

private:
    bool isLeapYear(int year);
};

#endif // DATEMETHODS_H
