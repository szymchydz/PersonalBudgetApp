#include "TextFile.h"

 string TextFile :: getFileName(){
        return FILENAME;
    }

    int TextFile :: getLastId() {
        return lastId;
    }

    bool TextFile :: isFileEmpty(fstream &TextFile) {

    TextFile.seekg(0, ios::end);
    if (TextFile.tellg() == 0)
        return true;
    else
        return false;
}
