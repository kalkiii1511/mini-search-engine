#ifndef TFIDFRANKER_HPP
#define TFIDFRANKER_HPP

#include "ranking/ranker.hpp"

class TFIDFRanker : public Ranker{
public:
    std::vector<SearchResult> rank(
        const std::unordered_map<std::string, int> &queryFreq,
        const std::vector<std::string> &uniqueTerms,
        const std::vector<const PostingList *> &postingLists,
        int totalDocs) const override;
};

#endif