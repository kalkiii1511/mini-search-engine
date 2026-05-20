#include "indexing/InvertedIndex.hpp"

void InvertedIndex::addTerm(const std::string &term, int docId) {
    index[term].addDocument(docId);
}

const PostingList* InvertedIndex::search(const std::string& term) const{
    auto it = index.find(term);
    if(it == index.end()){
        return nullptr;
    }
    return &(it->second);
}
