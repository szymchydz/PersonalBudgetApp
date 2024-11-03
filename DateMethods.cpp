#include "DateMethods.h"

string DateMethods::getTimeFromSystem() {
    time_t currentTime = time(nullptr);

    tm localTime = *localtime(&currentTime);

    char buffer[11];
    if (strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime) == 0) {
        cerr << "Blad formatu daty." << endl;
        return "";
    }
    return string(buffer);
}
string DateMethods::getPreviousMonthFromDate(string currentDate) {
    if (currentDate.size() != 10 || currentDate[4] != '-' || currentDate[7] != '-') {
        cout << "Bledny format" << endl;
        return "";
    }
    int currentMonthInt = stoi(currentDate.substr(5, 2));

    if (currentMonthInt == 1) {
        currentMonthInt = 12;
    } else if (currentMonthInt >= 2 && currentMonthInt <= 12) {
        currentMonthInt--;
    } else {
        cout << "Blad daty." << endl;
        return "";
    }
    stringstream previousMonthStream;
    previousMonthStream << setw(2) << setfill('0') << currentMonthInt;
    return previousMonthStream.str();
}

int DateMethods::checkNumberOfDaysPerMonth(int currentYear, int currentMonth) {
    if (currentMonth < 1 || currentMonth > 12) {
        return -1;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int lastDayOfCurrentDay = daysInMonth[currentMonth];

    if (currentMonth == 2) {
        if ((currentYear % 4 == 0 && currentYear % 100 != 0) || (currentYear % 400 == 0)) {
            lastDayOfCurrentDay = 29;
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
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year = getYearFromDate(date);
    int month = getMonthFromDate(date);
    int day = getDayFromDate(date);

    string currentDate = getTimeFromSystem();
    int currentYear = getYearFromDate(currentDate);
    int currentMonth = getMonthFromDate(currentDate);

    if (year < 2000 || year > currentYear) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    int lastDayOfMonth = checkNumberOfDaysPerMonth(year, month);

    if (day < 1 || day > lastDayOfMonth) {
        return false;
    }

    if (year == currentYear && month > currentMonth) {
        return false;
    }

    return true;
}

void DateMethods::displayDate(string displayedDate) {
    if (displayedDate.size() != 10 || displayedDate[4] != '-' || displayedDate[7] != '-') {
        cout << "Invalid date format" << endl;
        return;
    }

    cout << displayedDate.substr(8, 2) << '-'
         << displayedDate.substr(5, 2) << '-'
         << displayedDate.substr(0, 4) << endl;
}
string DateMethods::changeDateWithHyphenToDateWithoutHyphen(string date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return "";
    }
    string dateWithoutHyphen = date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);

    return dateWithoutHyphen;
}

string DateMethods::changeDateWithoutHyphenToDateWithHyphen(string date) {
    if (date.size() != 8) {
        return "";
    }

    string dateWithHyphen = date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2);

    return dateWithHyphen;
}
