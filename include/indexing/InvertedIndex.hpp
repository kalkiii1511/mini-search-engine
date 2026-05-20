#ifndef INVERTEDINDEX_HPP
#define INVERTEDINDEX_HPP

#include <unordered_map>
#include <string>
#include "indexing/postingList.hpp"

class InvertedIndex {
private:
    std::unordered_map<std::string,PostingList> index;

public:
    void addTerm(const std::string& term,int docId);
    const PostingList* search(const std::string& word) const;

};

#endif