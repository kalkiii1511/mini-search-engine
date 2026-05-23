#include <cassert>
#include <fstream>
#include <string>

#include "core/config.hpp"
#include "crawler/URLFrontier.hpp"
#include "crawler/URLNormalizer.hpp"
#include "crawler/crawler.hpp"
#include "storage/DocumentStorage.hpp"

class MemoryDocumentStorage : public DocumentStorage {
public:
    void saveDocument(const Document& doc) override {
        lastSaved = doc;
        hasSavedDocument = true;
    }

    Document loadDocument(int docId) const override {
        if (hasSavedDocument && lastSaved.getId() == docId) {
            return lastSaved;
        }

        return Document(docId, "", "");
    }

    void deleteDocument(int) override {
        hasSavedDocument = false;
    }

private:
    Document lastSaved = Document(0, "", "");
    bool hasSavedDocument = false;
};

void runCrawlerTests() {
    URLNormalizer normalizer;
    assert(normalizer.normalize(" HTTPS://Example.COM:443/path/#section ") ==
           "https://example.com/path");

    URLFrontier frontier;
    frontier.addURL("https://example.com");
    frontier.addURL("https://example.com");
    assert(frontier.hasNext());
    assert(frontier.getNext() == "https://example.com");
    assert(!frontier.hasNext());

    std::string emptySeedPath = "/tmp/search_engine_empty_seeds.txt";
    {
        std::ofstream out(emptySeedPath);
    }

    Indexer indexer;
    MemoryDocumentStorage storage;
    Config config(1, 1);
    Crawler crawler(indexer, storage, config);
    crawler.loadSeedURLs(emptySeedPath);
    assert(crawler.crawl() == 0);
}
