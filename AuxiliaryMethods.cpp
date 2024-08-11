#include "AuxiliaryMethods.h"

char AuxiliaryMethods :: getchar()
{
    string entry = "";
    char sign  = {0};

    while (true)
    {
        getline(cin, entry);

        if (entry.length() == 1)
        {
            sign = entry[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

string AuxiliaryMethods :: readLine()
{
    string entry = "";
    getline(cin, entry);
    return entry;
}
