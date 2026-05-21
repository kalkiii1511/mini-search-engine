#ifndef RANKER_HPP
#define RANKER_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "core/SearchResult.hpp"
#include "indexing/postingList.hpp"

class Ranker{
public:
    virtual std::vector<SearchResult> rank(
        const std::unordered_map<std::string, int> &queryFreq,
        const std::vector<std::string> &uniqueTerms,
        const std::vector<const PostingList *> &postingLists,
        int totalDocs) const = 0;

    virtual ~Ranker() = default;
};

#endif