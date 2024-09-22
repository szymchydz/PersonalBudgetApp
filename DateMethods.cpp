#include "DateMethods.h"

string DateMethods::getTimeFromSystem() {

    char bufor [ 64 ];
    time_t timeTakenFromComputer;
    time( & timeTakenFromComputer );
    tm timeTakenFromComputerTM = * localtime( & timeTakenFromComputer );
    strftime( bufor, sizeof( bufor ), "%Y-%m-%d", & timeTakenFromComputerTM );
    string date = bufor;

    return date;
}

int DateMethods::getYearFromDate(string date) {

    int year = AuxiliaryMethods::convertStringToInt(date.substr(0,4));

    return year;
}

int DateMethods::getMonthFromDate(string date) {

    int month = AuxiliaryMethods::convertStringToInt(date.substr(5,2));

    return month;
}

int DateMethods::getDayFromDate(string date) {

    int day = AuxiliaryMethods::convertStringToInt((date.substr(8,2)));

    return day;
}

int DateMethods::checkNumberOfDaysPerMonth(int currentYear, int currentMonth) {

    int lastDayOfCurrentDay;

    switch (currentMonth) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        lastDayOfCurrentDay = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        lastDayOfCurrentDay = 30;
        break;
    case 2: {
        if (((currentYear % 4 == 0) && (currentYear % 100 != 0)) || ((currentYear % 400 == 0)))
            lastDayOfCurrentDay = 29;
        else lastDayOfCurrentDay = 28;
        break;
    }

    }
    return lastDayOfCurrentDay;

}

string DateMethods::changeDateWithHypenToDateWithoutHyphen(string date) {

    string dateWithoutHyphen = (date.substr(0,4)) + (date.substr(5,2)) + (date.substr(8,2));

    return dateWithoutHyphen;
}

bool DateMethods::checkFormatDateIsCorrect(string date) {

    if ((date[4]=='-') && (date[7]=='-') && date.size()==10) {
        int year, month, day, lastDayOfMonth, currentYear, currentMonth;
        string currentDate;

        year = getYearFromDate(date);
        day = getDayFromDate(date);
        month = getMonthFromDate(date);

        currentDate = getTimeFromSystem();
        currentYear = getYearFromDate(currentDate);
        currentMonth = getMonthFromDate(currentDate);
        lastDayOfMonth = checkNumberOfDaysPerMonth(year, month);

        if ((year >= 2000) && (year <= currentYear)) {
            if ((month >= 1) && (month <= 12)) {
                if ((day >= 1) && (day <= lastDayOfMonth)) {
                    if (year == currentYear) {
                        if (month > currentMonth)
                            return false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
