#include "core/SearchEngine.hpp"

#include "query/QueryProcessor.hpp"

SearchEngine::SearchEngine() : totalDocs(0) {}

Document SearchEngine::prepareDocument(const Document& doc) {
    Document prepared = doc;

    if (prepared.getExtractedText().empty() && !prepared.getRawHTML().empty()) {
        DOMTree domTree = htmlParser.parse(prepared.getRawHTML());
        prepared.setExtractedText(textExtractor.extractText(&domTree));
    }

    return prepared;
}

void SearchEngine::addDocument(const Document& doc) {
    Document prepared = prepareDocument(doc);
    bool isNewDocument = documents.find(prepared.getId()) == documents.end();

    if (!isNewDocument) {
        return;
    }

    documents.insert_or_assign(prepared.getId(), prepared);
    indexer.addDocument(prepared);
    totalDocs++;
}

int SearchEngine::crawlFromSeeds(
    const std::string& seedFilePath,
    DocumentStorage& storage,
    const Config& config) {
    Crawler crawler(indexer, storage, config);
    crawler.loadSeedURLs(seedFilePath);

    int crawledCount = crawler.crawl();
    totalDocs += crawledCount;

    return crawledCount;
}

std::vector<SearchResult> SearchEngine::search(const std::string& query) {
    QueryProcessor processor(indexer, ranker, totalDocs);
    return processor.search(query);
}

const Document* SearchEngine::getDocument(int docId) const {
    auto it = documents.find(docId);
    if (it == documents.end()) {
        return nullptr;
    }

    return &it->second;
}

int SearchEngine::getDocumentCount() const {
    return totalDocs;
}
