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

string DateMethods::getPreviousMonthFromDate(string currentDate) {

    string currentMonth, previousMonth;
    int currentMonthInt;

    currentMonth = currentDate.substr(5,2);
    currentMonthInt = (currentMonth[0]-48)*10 + currentMonth[1] - 48;

    if((currentMonthInt > 1) && (currentMonthInt <= 12)) {
        currentMonthInt--;
    } else if (currentMonthInt == 1) {
        currentMonthInt = 12;
    } else {
        cout << "Blad daty." << endl;
    }

    previousMonth = AuxiliaryMethods::convertIntToString(currentMonthInt);

    if (previousMonth.size()==1)
        previousMonth = "0" + previousMonth;

    return previousMonth;
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

void DateMethods::displayDate (string displayedDate) {

    for (int i = 8; i <= 9; i++) {
        cout << displayedDate[i];
    }
    for (int i = 4; i <= 7; i++) {
        cout << displayedDate[i];
    }
    for (int i = 0; i <= 3; i++) {
        cout << displayedDate[i];
    }
}

string DateMethods::changeDateWithHyphenToDateWithoutHyphen(string date) {

    string dateWithoutHyphen = (date.substr(0,4)) + (date.substr(5,2)) + (date.substr(8,2));

    return dateWithoutHyphen;
}

string DateMethods::changeDateWithoutHyphenToDateWithHyphen(string date) {

    string dateWithHyphen = (date.substr(0,4)) + (date.substr(4,2)) + (date.substr(6,2));
    dateWithHyphen.insert(4, "-");
    dateWithHyphen.insert(7, "-");

    return dateWithHyphen;
}
