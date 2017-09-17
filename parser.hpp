#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "document.hpp"
#include "query.hpp"
#include "result.hpp"
#include <math.h>
#include <map>
#include <set>

using namespace std;

// enum Tag {PN, RN, AN, AU, TI, SO, MJ, MN, AB, EX, RF, CT, NIL};

class Parser{

    private:
        string path;
        int n_documents;
        int n_queries;


    public:
        Parser();
        vector<Document> ProcessDocuments();
        vector<Query> ProcessQueries();
        unordered_map<string, unordered_map<int, int> > getVocabulary(vector<Document>);
        unordered_map<string, double> getIdfs(unordered_map<string, unordered_map<int, int> >);
        map<int, vector<double> > getWeight(unordered_map<string, double>, unordered_map<string, unordered_map<int, int> >, vector<Document>);
        void processQuery(unordered_map<string, double>, unordered_map<string, unordered_map<int, int> >, map<int, vector<double> >, Query);
};
#endif