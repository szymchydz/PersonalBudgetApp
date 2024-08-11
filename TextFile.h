#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "Markup.h"
#include <string>

using namespace std;

class TextFile {
    const string FILENAME;
    int lastId;
    CMarkup xmlDoc;


public:
    TextFile(const string& fileName) : FILENAME(fileName), lastId(0) {}

    string getFileName() const {
        return FILENAME;
    }

    int getLastId() const {
        return lastId;
    }
};

#endif
