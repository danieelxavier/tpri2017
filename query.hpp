#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Query{

    public:
        Query();

        int queryNumber;
        int nRelevants;
        string query;
        int docsRelevants[1239];
};


#endif