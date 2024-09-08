#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <iostream>
#include <fstream>

#include "Markup.h"

using namespace std;

class TextFile {
    const string FILENAME;

protected:
    int lastId;
    CMarkup xmlDoc;

    TextFile(const string& fileName) : FILENAME(fileName), lastId(0) {}

    static bool isFileEmpty(fstream &TextFile);
    string getFileName();

public:
    int getLastId();
};

#endif // TEXTFILE_H
