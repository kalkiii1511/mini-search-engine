#include <bits/stdc++.h>

using namespace std;
using ll=long long;

class Document{
private:
    int id;
    string content;

public:
    Document(int id,const string& content){
        this->id=id;
        this->content=content;
    }
    int getId() const{
        return id;
    }
    string getContent() const{
        return content;
    }
};

class searchResult
{
public:
    int docID;
    int Freq;
    searchResult(int docID, int Freq)
    {
        this->docID = docID;
        this->Freq = Freq;
    }
};

class Parser{
public:
    vector<string> parse(const string& content){
        vector<string> words;
        string buffer="";
        for(char c:content){
            if(isalnum(c)){
                buffer+=tolower(c);
            }
            else{
                if(buffer.size()){
                    words.push_back(buffer);
                    buffer.clear();
                }
            }
        }

        if(!buffer.empty()){
            words.push_back(buffer);
        }

        return words;
    }
};

class Indexer{
private:
    unordered_map<string, unordered_map<int, int>> index;

public:
    void addDocument(const Document &doc, Parser &p){
        vector<string> words = p.parse(doc.getContent());
        int id = doc.getId();

        for (const string &word : words){
            index[word][id]++;
        }
    }

    vector<searchResult> search(const string& word){
        vector<searchResult> results;
        auto it=index.find(word);
        if(it==index.end()) return results;
        for(auto [docID,Freq]:it->second){
            results.push_back(searchResult(docID,Freq));
        }
        return results;
    }
};

class QueryProcessor
{
private:
    Parser parser;
    unordered_set<string> stopWords = {"the", "is", "a", "an", "of", "to"};

public:
    vector<string> process(const string &query)
    {
        vector<string> words = parser.parse(query);
        vector<string> filtered;
        for (string word : words)
        {
            if (!stopWords.count(word))
            {
                filtered.push_back(word);
            }
        }
        return filtered;
    }
};

class SearchEngine{
private:
    Parser parser;
    Indexer indexer;
    QueryProcessor processor;
    unordered_map<int, int> computeScores(const vector<string> &words)
    {
        unordered_map<int, int> scores;
        for (const string& word : words)
        {
            auto result = indexer.search(word);
            for (auto [docID, Freq] : result)
            {
                scores[docID] += Freq;
            }
        }
        return scores;
    }

public:
    void addDocument(const Document& doc){
        indexer.addDocument(doc,parser);
    }
    vector<searchResult>search(const string& query){
        vector<string> words=processor.process(query);
        auto scores=computeScores(words);

        vector<searchResult> results;
        for(auto [docID,score]:scores){
            results.push_back(searchResult(docID,score));
        }
        
        sort(results.begin(),results.end(),[](const searchResult& a,const searchResult& b){return a.Freq>b.Freq;});

        return results;
    }

};


int main()
{
    SearchEngine engine;

    Document d1(1, "Apple makes iPhone");
    Document d2(2, "Microsoft makes Windows");
    Document d3(3, "Apple sells Macbook");
    Document d4(4, "iPhone is made by Apple");

    engine.addDocument(d1);
    engine.addDocument(d2);
    engine.addDocument(d3);
    engine.addDocument(d4);

    while (true)
    {
        string query;

        cout << "Enter query (type exit to quit): ";
        getline(cin, query);

        if (query == "exit")
        {
            break;
        }

        vector<searchResult> results = engine.search(query);

        if (results.empty())
        {
            cout << "No results found\n";
            continue;
        }

        for (const auto &result : results)
        {
            cout << "Doc ID: " << result.docID
                 << " Score: " << result.Freq << endl;
        }
    }

    return 0;
}