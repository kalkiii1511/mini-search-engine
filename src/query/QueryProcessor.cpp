#include "query/QueryProcessor.hpp"
#include <unordered_map>
#include <unordered_set>

QueryProcessor::QueryProcessor(
    Indexer &indexer, Ranker &ranker, int totalDocs)
    :indexer(indexer),ranker(ranker),totalDocs(totalDocs) {}

std::vector<SearchResult> QueryProcessor::search(const std::string &query) const{
    std::vector<std::string> words = parser.parse(query);

    std::unordered_map<std::string,int> queryfreq;
    std::unordered_set<std::string> seen;
    std::vector<std::string> uniqueTerms;
    std::vector<const PostingList*> postingLists;

    for(const auto& word : words){
        queryfreq[word]++;

        if(seen.find(word)!=seen.end()){
            continue;
        }
        seen.insert(word);

        uniqueTerms.push_back(word);
        postingLists.push_back(indexer.search(word));
    }

    return ranker.rank(queryfreq,uniqueTerms,postingLists,totalDocs);
}
