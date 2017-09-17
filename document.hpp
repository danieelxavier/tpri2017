#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Document{

    public:
        Document();

        string paperNumber;
        int recordNumber;
        string title;
        string abstract;
};


#endif