#include "parser.hpp"

Parser::Parser(){

}

int nStopWords = 319;
string stopWords[319];

bool comparator (double i,double j) { return (i>j); }

bool startsWith(const std::string& text,const std::string& token)
{
	if(text.length() < token.length())
		return false;
	return (text.compare(0, token.length(), token) == 0);
}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void stringToUpper(string &s)
{
   for(unsigned int l = 0; l < s.length(); l++)
  {
    s[l] = toupper(s[l]);
  }
}

const vector<string> split(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

bool verifyStopWords(string string){

    int i;
    for(i = 0; i < nStopWords; i++){
        if (string.compare(stopWords[i]) == 0){
            return true;
        }
    }
    return false;
}

void intercalar (pair<int, double> v[], pair<int, double> aux[],int ini1, int ini2,int fim2)
{
    int in1=ini1,in2=ini2,fim1=in2-1,au=0,i;
    while(in1<=fim1 && in2<=fim2)
    {
        if (v[in1].second > v[in2].second)
        {
            aux[au++] = v[in1++];
        }
        else
        {
            aux[au++] = v[in2++];
        }
    }
    while(in1<=fim1)
    {
        aux[au++] = v[in1++];
    }
    while(in2<=fim2)
    {
        aux[au++] = v[in2++];
    }

    for(i=0;i<au;i++){
        v[i+ini1]=aux[i];
    }
}

void mergeSort (pair<int, double> v[],int esq, int dir)
{
    int meio,i;
    pair<int, double> aux[dir+1];
    if(esq<dir)
    {
        meio=(esq+dir)/2;
        mergeSort(v,esq,meio);
        mergeSort(v,meio+1,dir);
        intercalar(v,aux,esq,meio+1,dir);  
    }
}

vector<Document> Parser::ProcessDocuments(){
    int year = 74;
    vector<Document> docs;

    while(year < 80){
    
        string line;
        ifstream myfile ("cfc/cf" + to_string(year));
        // ifstream myfile ("text.txt");

        if (myfile.is_open()){
            while (!myfile.eof())
            {
                Document doc;
                do{

                    //PAPER NUMBER
                    if(startsWith(line, "PN")){
                        line.erase(0,3);
                        line = trim(line);
                        stringToUpper(line);

                        doc.paperNumber = line;
                    }

                    //RECORD NUMBER
                    if(startsWith(line, "RN")){
                        line.erase(0,3);
                        line = trim(line);
                        stringToUpper(line);

                        doc.recordNumber = stoi(line);

                    }

                    // TITLE
                    if(startsWith(line, "TI")){
                        
                        string aux = "";
						
						while (startsWith(line, "TI") || startsWith(line, " ")) {
							line = line.erase(0,3);
							line = trim(line);
                            stringToUpper(line); 
						
							aux = aux + line + " ";
							
							getline(myfile, line);
						}

                        doc.title = trim(aux);
                    }

                    // ABSTRACT
                    if(startsWith(line, "AB") || startsWith(line, "EX")){
                        
                        string aux = "";
						
						while (startsWith(line, "AB") || startsWith(line, "EX") || startsWith(line, " ")) {
							line = line.erase(0,3);
							line = trim(line);
                            stringToUpper(line); 
						
							aux = aux + line + " ";
							
							getline(myfile, line);
						}

                        doc.abstract = aux;
                    }

                    getline(myfile, line);
                } while(!startsWith(line, "PN") && !myfile.eof());

                if(!doc.paperNumber.empty())
                    docs.push_back(doc);

            }
            myfile.close();
        }
        else cout << "Unable to open file"; 

        year++;
        
    }

    n_documents = docs.size();

    return docs;
}

vector<Query> Parser::ProcessQueries(){

    vector<Query> queries;

    string line;
    ifstream myfile ("cfc/cfquery");
    // ifstream myfile ("text.txt");

    if (myfile.is_open()){
        while (!myfile.eof())
        {
            bool flag = false;
            
            Query query;
            do{
                //QUERY NUMBER
                if(startsWith(line, "QN")){
                    line.erase(0,3);
                    line = trim(line);
                    stringToUpper(line);
                    flag = true;

                    query.queryNumber = stoi(line);
                    // cout << query.queryNumber << endl;
                }

                // QUERY
                if(startsWith(line, "QU")){
                    
                    string aux = "";
                    
                    while (startsWith(line, "QU") || startsWith(line, " ")) {
                        line = line.erase(0,3);
                        line = trim(line);
                        stringToUpper(line); 
                    
                        aux = aux + line + " ";
                        
                        getline(myfile, line);
                    }

                    query.query = trim(aux);
                }

                // NUMBER OF RELEVANTS
                if(startsWith(line, "NR")){
                    line.erase(0,3);
                    line = trim(line);
                    stringToUpper(line);

                    query.nRelevants = stoi(line);

                }

                // DOCUMENTS RELEVANTS
                if(startsWith(line, "RD")){

                    vector<int> docsRelevants;

                    // cout << query.queryNumber << endl;

                    while (startsWith(line, "RD") || startsWith(line, "   ")) {
                        line = line.erase(0,3);
                        line = trim(line);
        
                        vector<string> docsRelString = split(line, ' ');

                        // cout << "=" << line << "+" << docsRelString.size() << endl;

                        unsigned int d;
                        for(d = 0; d < docsRelString.size(); d += 2){
                            docsRelevants.push_back(stoi(docsRelString[d]));
                            // cout << "=>" << docsRelString[d] << endl;
                        }
                        getline(myfile, line);

                    }

                    // query.docsRelevants.clear();
                    // query.docsRelevants.clear();
                    
                    // query.docsRelevants = docsRelevants;
                    unsigned int i;
                    // cout << "size: " << docsRelevants.size() << endl;
                    for(i = 0; i < docsRelevants.size(); i++) {
                        // cout << docsRelevants[i] << endl;;
                        query.docsRelevants[i] = docsRelevants[i];
                    } 

                    // cout << "size: " << query.docsRelevants.size() << endl;
                    

                }

                if(!startsWith(line, "QN"))
                    getline(myfile, line);
            } while(!startsWith(line, "QN") && !myfile.eof());

            if(flag)
                queries.push_back(query);

        }
        myfile.close();
    }
    else cout << "Unable to open file"; 


    n_queries = queries.size();

    return queries;
}

void Parser::ProcessStopWords(){
    

        string line;
        ifstream myfile ("stopwords");
        // ifstream myfile ("text.txt");
    
        int c = 0;
        if (myfile.is_open()){
            while (!myfile.eof())
            {
                string sw = line;
                stopWords[c] = sw;
                c++;

                getline(myfile, line);
            }
            myfile.close();
        }
        else cout << "Unable to open file"; 

        // for (auto w : this->stopWords){
        //     cout << w << endl;
        // }
    
    }


unordered_map<string, int> getTFs(const string &s, char delim) {
    stringstream ss(s);
    string item;
    unordered_map<string, int> tokens;
    while (getline(ss, item, delim)) {

        string newItem;

        for( string::iterator it = item.begin(); it != item.end(); ++it )
        {
            if( (*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') )
            {
                newItem += *it;
            }
        }

        newItem = trim(newItem);


        if(!newItem.empty()){
            if(verifyStopWords(newItem)){
                pair<string, int> pair (newItem,0);
                tokens.insert(pair);
                tokens.at(newItem)++;
            }
        }
    }
    return tokens;
}

unordered_map<string, unordered_map<int, int> > Parser::getVocabulary(vector<Document> docs){
    
    unordered_map<string, unordered_map<int, int> > vocabulary;
    
    for(vector<Document>::iterator it = docs.begin(); it != docs.end(); ++it) {

        string strDoc;
        
        strDoc = it->title;
        strDoc = strDoc + " " + it->abstract;

        // cout << it->paperNumber << endl << it->title << endl << strDoc << endl << endl;

        unordered_map<string,int> words = getTFs(strDoc, ' ');


        for (auto& word: words)
        {
            pair<int, int> docCount (it->recordNumber, word.second);
            
            if (vocabulary.find(word.first) == vocabulary.end()){ //verify if key is in using
                unordered_map<int, int> docCounts;
                docCounts.insert(docCount);

                pair<string, unordered_map<int, int> > pair (word.first, docCounts);
                vocabulary.insert(pair);
            }
            else{
                vocabulary.at(word.first).insert(docCount);
            }

        }

        

    }

    return vocabulary;
}

unordered_map<string, double> Parser::getIdfs(unordered_map<string, unordered_map<int, int> > vocabulary){

    unordered_map<string, double> idfs;

    for (auto& word: vocabulary)
    {
        double idf = log10((double)n_documents/(double)word.second.size());

        pair<string, double> pair (word.first, idf);

        idfs.insert(pair);
    }


    return idfs;
}

unordered_map<int, vector<double> > Parser::getWeight(unordered_map<string, double> idfs, unordered_map<string, unordered_map<int, int> > vocabulary, vector<Document> docs){

    unordered_map<int, vector<double> > weights;

    for(auto& doc: docs){

        vector<double> wDoc;

        for(auto& word: vocabulary){
            
            int tf = 0;

            if(word.second.count(doc.recordNumber) > 0){
                tf = word.second.at(doc.recordNumber);
            }

            double idf = idfs.at(word.first);

            double w = idf * (double)tf;
            wDoc.push_back(w);

        }

        weights.insert(pair<int, vector<double> >(doc.recordNumber, wDoc));

    }

    return weights;
}

vector<pair<int, double> > Parser::processQuery(unordered_map<string, double> idfs, unordered_map<string, unordered_map<int, int> > vocabulary, unordered_map<int, vector<double> > wDocs, Query query){
    
    unordered_map<string,int> words = getTFs(query.query, ' ');
    


    double wQuery[vocabulary.size()];


    int c = 0;
    for(auto& word: vocabulary){
        
        int tf = 0;

        // if(words.find(word.first) != words.end()){
            auto t = words.find(word.first);
            if(t != words.end())
                tf = t->second;

            // cout << word.first << endl;
        // }

        double idf = idfs.at(word.first);

        double w = idf * (double)tf;
        wQuery[c] = w;

        c++;
    }

    pair<int, double> sims[wDocs.size()];

    int i;
    
    for(i=1; i < wDocs.size(); i++){

        double num = 0;
        double den1 = 0;
        double den2 = 0;
        
        int j;
        for(j=0; j < wDocs[i].size(); j++){

            if(wDocs[i][j] > 0){
                num += (wDocs[i][j] * wQuery[j]);

                den1 += pow(wDocs[i][j], 2);
            }

            den2 += pow(wQuery[j], 2);
        }

        double sim = num / (sqrt(den1) * sqrt(den2));

        pair<int, double> sd (i, sim);
        sims[i] = sd;     


        // cout << i << " - " << sim << endl;
        
    }

    mergeSort(sims, 0, wDocs.size()-1);


    vector<pair<int, double> > similarities;
    int p;
    int t = 1;
    for (p=0;p<wDocs.size();p++){
        std::cout << t << "\t-\t" << sims[p].first << "\t-\t" << sims[p].second << endl; 
        if(sims[p].second > 0)
            similarities.push_back(sims[p]);
        t++;
    }


    return similarities;
}




//Método que retorna o número de documentos relevantes em um ponto N do ranking de similaridades
int relevantesRetornados(Query query, int N){
    
    int c = 0;
    for (int i = 0; i < N; i++) {
        if(isRelevante(consulta, consulta.getSimilaridades().get(i).getDocumento())){
                c++;
        }
    }
    return c;
}

//Método que verifica se um documento é relevante para uma consulta
bool isRelevante(Consulta consulta, int documento){

    for (AvaliacaoConsulta ac : consulta.getAvaliacoes()) {
        
        if(ac.getRecordNumber() == documento){
            return true;
        }
    }
    return false;
}

double Parser::precisionN(vector<pair<int, double> > sims, Query q){
    
}

double Parser::calculeMAP(vector<pair<int, double> > sims, Query q){

}
