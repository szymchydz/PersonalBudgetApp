#include "DateMethods.h"

string DateMethods::getTimeFromSystem(const std::string& format) {
        // Pobierz obecny czas jako obiekt time_t
        std::time_t currentTime = std::time(nullptr);

        // SprawdŸ, czy pobranie czasu siê powiod³o
        if (currentTime == -1) {
            std::cerr << "Nie uda³o siê pobraæ obecnego czasu." << std::endl;
            return ""; // Obs³uga b³êdu
        }

        // Przekszta³æ do lokalnego czasu
        std::tm localTime;
#ifdef _WIN32
        localtime_s(&localTime, &currentTime); // Dla Windows
#else
        localtime_r(&currentTime, &localTime); // Dla systemów POSIX
#endif

        // Sformatuj datê
        char buffer[100]; // Bufor do przechowywania sformatowanej daty
        std::strftime(buffer, sizeof(buffer), format.c_str(), &localTime);

        return std::string(buffer); // Zwróæ jako std::string
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
        // Check if the date string is in the correct format (YYYY-MM-DD)
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            cerr << "Invalid date format. Please use YYYY-MM-DD." << endl;
            return ""; // Return an empty string or handle the error as needed
        }

        // Extract parts of the date and concatenate them
        string dateWithoutHyphen = date.substr(0, 4) + date.substr(5, 2) + date.substr(8, 2);

        return dateWithoutHyphen;
    }

string DateMethods::changeDateWithoutHypenToDateWithHyphen(string date) {

    string dateWithHyphen = (date.substr(0,4)) + (date.substr(4,2)) + (date.substr(6,2));
    dateWithHyphen.insert(4, "-");
    dateWithHyphen.insert(7, "-");

    return dateWithHyphen;
}

bool DateMethods::checkFormatDateIsCorrect(string date) {

    if ((date[4]=='-') && (date[7]=='-') && date.size()==10) {
        int year, month, day, lastDayOfMonth, currentYear, currentMonth;
        string currentDate;

        year = getYearFromDate(date);
        day = getDayFromDate(date);
        month = getMonthFromDate(date);

        currentDate = getTimeFromSystem("%Y-%m-%d");
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

string DateMethods :: getStartDate(const string& currentDate) {
    return currentDate.substr(0, 4) + currentDate.substr(5, 2) + "01";
}

string DateMethods :: getEndDate(const string& currentDate) {
    int year = dateMethods.getYearFromDate(currentDate);
    int month = dateMethods.getMonthFromDate(currentDate);
    int daysInMonth = dateMethods.checkNumberOfDaysPerMonth(year, month);
    return currentDate.substr(0, 4) + currentDate.substr(5, 2) + AuxiliaryMethods::convertIntToString(daysInMonth);
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
