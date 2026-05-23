#include <cassert>
#include <vector>

#include "core/document.hpp"
#include "query/QueryProcessor.hpp"
#include "ranking/TFIDFRanker.hpp"

void runQueryProcessorTests() {
    Indexer indexer;
    TFIDFRanker ranker;

    Document first(1, "memory://apple", "");
    first.setExtractedText("apple iphone");
    indexer.addDocument(first);

    Document second(2, "memory://windows", "");
    second.setExtractedText("windows laptop");
    indexer.addDocument(second);

    QueryProcessor processor(indexer, ranker, 2);
    std::vector<SearchResult> results = processor.search("the apple");

    assert(!results.empty());
    assert(results[0].getId() == 1);
    assert(results[0].getScore() > 0.0);
}
