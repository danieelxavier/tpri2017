#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "document.hpp"
#include "query.hpp"
#include "parser.hpp"

using namespace std;



int main(){

    Parser p;
    vector<Document> docs = p.ProcessDocuments();
    vector<Query> queries = p.ProcessQueries();

    unordered_map<string, unordered_map<int, int> > voc = p.getVocabulary(docs);
    unordered_map<string, double> idfs = p.getIdfs(voc);
    
    map<int, vector<double> > weights = p.getWeight(idfs, voc, docs);

    p.processQuery(idfs, voc, weights, queries[0]);


    // ofstream vocab, idffile, wfs;
    // vocab.open ("output/vocabulary.txt");

    // for (auto& word: voc)
    // {
    //     vocab << word.first << " (" << word.second.size() << ") - ";

    //     for (auto& c: word.second)
    //     {
    //         vocab << "(" << c.first << ", " << c.second << ") ";
    //     }
    //     vocab << endl;
    // }
    // vocab.close();

    // idffile.open("output/idfs.txt");

    // for (auto& idf: idfs)
    // {
    //     idffile << idf.first << " - " << idf.second << endl;

    // }


    // idffile.close();

    // wfs.open("output/weightsFile.txt");
    
    // int i;
    // for (i = 1; i <= docs.size(); i++)
    // {
    //     wfs << i << " - (";

    //     for(auto& w: weights[i]){
    //         wfs << w << ", ";
    //     }

    //     wfs << ")" << endl;

    // }
    
    // wfs.close();

    // for(std::vector<Query>::iterator it = queries.begin(); it != queries.end(); ++it) {
        
    //     cout << "QN: " << it->queryNumber << endl;
    //     cout << "QU: " << it->query << endl;
    //     cout << "NR: " << it->nRelevants << endl;
    //     cout << "RD: (";

    //     int po;
    //     for(po = 0; po < it->nRelevants; po++) {
            
    //         cout << it->docsRelevants[po] << ", ";
            
    //     }

    //     cout << ")" << endl << endl;

    // }
        
    // cout << docs.size() << endl;
    
    return 0;
}