#ifndef QUERYPROCESSOR_HPP
#define QUERYPROCESSOR_HPP

#include <vector>
#include <string>


#include "ranking/ranker.hpp"
#include "indexing/Indexer.hpp"
#include "query/QueryParser.hpp"
#include "core/SearchResult.hpp"

class QueryProcessor {
private:
    QueryParser parser;
    Indexer& indexer;
    Ranker& ranker;
    int totalDocs;

public:
    QueryProcessor(Indexer& indexer,Ranker& ranker,int totalDocs);
    std::vector<SearchResult> search(const std::string& query) const;
};


#endif