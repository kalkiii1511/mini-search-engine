#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "core/SearchResult.hpp"
#include "core/config.hpp"
#include "crawler/crawler.hpp"
#include "core/document.hpp"
#include "indexing/Indexer.hpp"
#include "parser/HTMLParser.hpp"
#include "parser/TextExtractor.hpp"
#include "ranking/TFIDFRanker.hpp"
#include "storage/DocumentStorage.hpp"

class SearchEngine {
private:
    Indexer indexer;
    TFIDFRanker ranker;
    HTMLParser htmlParser;
    TextExtractor textExtractor;
    std::unordered_map<int, Document> documents;
    int totalDocs;

    Document prepareDocument(const Document& doc);

public:
    SearchEngine();

    void addDocument(const Document& doc);
    int crawlFromSeeds(
        const std::string& seedFilePath,
        DocumentStorage& storage,
        const Config& config);
    std::vector<SearchResult> search(const std::string& query);
    const Document* getDocument(int docId) const;
    int getDocumentCount() const;
};

#endif
