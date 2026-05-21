#ifndef POSTINGLIST_HPP
#define POSTINGLIST_HPP
#include <unordered_map>

class PostingList {
private:
    std::unordered_map<int,int> postings;
public:
    void addDocument(const int docId);
    const std::unordered_map<int,int>& getPostings() const;
    int getDocumentFrequency() const;
};

#endif