#include "DateMethods.h"

string DateMethods::getTimeFromSystem() {
    time_t currentTime = time(nullptr);
    tm localTime = *localtime(&currentTime);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
    return string(buffer);
}

int DateMethods::checkNumberOfDaysPerMonth(int currentYear, int currentMonth) {
    if (currentMonth < 1 || currentMonth > 12) return -1;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (currentMonth == 2 && isLeapYear(currentYear)) return 29;
    return daysInMonth[currentMonth - 1];
}

bool DateMethods::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool DateMethods::checkFormatDateIsCorrect(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 2000 || month < 1 || month > 12 || day < 1 || day > checkNumberOfDaysPerMonth(year, month)) return false;
    return true;
}

string DateMethods::changeDateWithHyphenToDateWithoutHyphen(const string& date) {
    return date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);
}

string DateMethods::changeDateWithoutHyphenToDateWithHyphen(const string& date) {
    return date.substr(0, 4) + "-" + date.substr(4, 2) + "-" + date.substr(6, 2);
}

void DateMethods::displayDate(const string& displayedDate) {
    if (displayedDate.size() != 10 || displayedDate[4] != '-' || displayedDate[7] != '-') {
        cout << "Invalid date format" << endl;
        return;
    }
    cout << displayedDate.substr(8, 2) << '-'
         << displayedDate.substr(5, 2) << '-'
         << displayedDate.substr(0, 4) << endl;
}

int DateMethods::getYearFromDate(const string& date) {
    return stoi(date.substr(0, 4));
}

int DateMethods::getMonthFromDate(const string& date) {
    return stoi(date.substr(5, 2));
}

string DateMethods::getPreviousMonthFromDate(const string& currentDate) {
    if (currentDate.size() != 10 || currentDate[4] != '-' || currentDate[7] != '-') {
        cout << "Invalid date format" << endl;
        return "";
    }

    int currentMonthInt = stoi(currentDate.substr(5, 2));

    if (currentMonthInt == 1) {
        currentMonthInt = 12;
    } else if (currentMonthInt >= 2 && currentMonthInt <= 12) {
        currentMonthInt--;
    } else {
        cout << "Invalid date." << endl;
        return "";
    }

    stringstream previousMonthStream;
    previousMonthStream << setw(2) << setfill('0') << currentMonthInt;
    return previousMonthStream.str();
}
