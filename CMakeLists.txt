cmake_minimum_required(VERSION 3.16)

project(SearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)

set(SEARCH_ENGINE_CORE_SOURCES
    src/core/SearchEngine.cpp
    src/core/SearchResult.cpp
    src/core/document.cpp
    src/crawler/HTTPClient.cpp
    src/crawler/RobotsChecker.cpp
    src/crawler/URLFrontier.cpp
    src/crawler/URLNormalizer.cpp
    src/crawler/crawler.cpp
    src/indexing/Indexer.cpp
    src/indexing/InvertedIndex.cpp
    src/indexing/postingList.cpp
    src/indexing/stemmer.cpp
    src/indexing/stopWordRemover.cpp
    src/parser/DOMNode.cpp
    src/parser/DOMTree.cpp
    src/parser/HTMLParser.cpp
    src/parser/LinkExtractor.cpp
    src/parser/TextExtractor.cpp
    src/parser/Tokenizer.cpp
    src/query/QueryParser.cpp
    src/query/QueryProcessor.cpp
    src/ranking/TFIDFRanker.cpp
    src/storage/FileDocumentStorage.cpp
)

add_library(search_engine_core ${SEARCH_ENGINE_CORE_SOURCES})
target_include_directories(search_engine_core PUBLIC include)
target_link_libraries(search_engine_core PUBLIC CURL::libcurl)

add_executable(search_engine src/main.cpp)
target_link_libraries(search_engine PRIVATE search_engine_core)
target_link_libraries(search_engine PRIVATE CURL::libcurl)

enable_testing()

add_executable(search_engine_tests
    tests/parser/ParserTests.cpp
    tests/parser/HTMLParserTests.cpp
    tests/indexing/IndexerTests.cpp
    tests/indexing/StemmerTests.cpp
    tests/query/QueryProcessorTests.cpp
    tests/ranking/RankerTests.cpp
    tests/crawler/CrawlerTests.cpp
    tests/storage/StorageTests.cpp
)

target_link_libraries(search_engine_tests PRIVATE search_engine_core)
add_test(NAME search_engine_tests COMMAND search_engine_tests)
