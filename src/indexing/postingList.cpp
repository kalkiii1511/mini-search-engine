#include "indexing/postingList.hpp"

void PostingList::addDocument(const int docId){
    postings[docId]++;
}

const std::unordered_map<int, int>& PostingList::getPostings() const{
    return postings;
}

int PostingList::getDocumentFrequency() const{
    return postings.size();
}