#include <iostream>
#include <stdexcept>
#include <vector>

#include "core/config.hpp"
#include "core/SearchEngine.hpp"
#include "storage/FileDocumentStorage.hpp"

int main(int argc, char* argv[]) {
    SearchEngine engine;
    FileDocumentStorage storage;
    Config config(10, 3);
    std::string seedFilePath = "data/seeds.txt";

    if (argc > 1) {
        seedFilePath = argv[1];
    }

    try {
        int crawledPages = engine.crawlFromSeeds(seedFilePath, storage, config);
        std::cout << "Crawled and indexed documents: " << crawledPages << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Failed to crawl seed URLs: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "Enter query (type exit to quit): ";

    std::string query;
    while (std::getline(std::cin, query)) {
        if (query == "exit") {
            break;
        }

        std::vector<SearchResult> results = engine.search(query);

        if (results.empty()) {
            std::cout << "No results found\n";
        } else {
            for (const SearchResult& result : results) {
                std::cout << "Doc ID: " << result.getId()
                          << " Score: " << result.getScore();

                try {
                    Document doc = storage.loadDocument(result.getId());
                    std::cout << " URL: " << doc.getURL();
                } catch (const std::exception&) {
                }

                std::cout << "\n";
            }
        }

        std::cout << "Enter query (type exit to quit): ";
    }

    return 0;
}
