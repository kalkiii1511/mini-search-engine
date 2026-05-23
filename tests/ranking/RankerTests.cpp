#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

#include "ranking/TFIDFRanker.hpp"

void runRankerTests() {
    PostingList applePostings;
    applePostings.addDocument(1);
    applePostings.addDocument(1);
    applePostings.addDocument(2);

    std::unordered_map<std::string, int> queryFreq = {{"apple", 1}};
    std::vector<std::string> uniqueTerms = {"apple"};
    std::vector<const PostingList*> postingLists = {&applePostings};

    TFIDFRanker ranker;
    std::vector<SearchResult> results =
        ranker.rank(queryFreq, uniqueTerms, postingLists, 2);

    assert(results.size() == 2);
    assert(results[0].getId() == 1);
    assert(results[0].getScore() > results[1].getScore());
}
