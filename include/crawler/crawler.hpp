#ifndef CRAWLER_HPP
#define CRAWLER_HPP

#include <string>

#include "crawler/HTTPClient.hpp"
#include "crawler/URLFrontier.hpp"
#include "crawler/URLNormalizer.hpp"
#include "crawler/RobotsChecker.hpp"

#include "parser/HTMLParser.hpp"
#include "parser/TextExtractor.hpp"
#include "parser/LinkExtractor.hpp"

#include "indexing/Indexer.hpp"
#include "storage/DocumentStorage.hpp"
#include "core/config.hpp"

class Crawler {
private:
    HTTPClient httpClient;
    URLFrontier frontier;
    URLNormalizer normalizer;
    RobotsChecker robotsChecker;

    HTMLParser htmlParser;
    TextExtractor textExtractor;
    LinkExtractor linkExtractor;

    Indexer &indexer;
    DocumentStorage &storage;
    const Config &config;

    int nextDocId;

public:
    Crawler(
        Indexer &indexer,
        DocumentStorage &storage,
        const Config &config);

    void addSeedURL(const std::string &url);
    void loadSeedURLs(const std::string &filePath);
    int crawl();
};

#endif
