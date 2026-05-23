#include <cassert>
#include <iostream>
#include <vector>

#include "parser/Tokenizer.hpp"

void runHTMLParserTests();
void runIndexerTests();
void runStemmerTests();
void runQueryProcessorTests();
void runRankerTests();
void runCrawlerTests();
void runStorageTests();

void runParserTests() {
    Tokenizer tokenizer;

    std::vector<std::string> tokens =
        tokenizer.tokenize("Apple makes iPhone!! Version 15.");

    assert(tokens.size() == 5);
    assert(tokens[0] == "apple");
    assert(tokens[1] == "makes");
    assert(tokens[2] == "iphone");
    assert(tokens[3] == "version");
    assert(tokens[4] == "15");
}

int main() {
    runParserTests();
    runHTMLParserTests();
    runIndexerTests();
    runStemmerTests();
    runQueryProcessorTests();
    runRankerTests();
    runCrawlerTests();
    runStorageTests();

    std::cout << "All tests passed\n";
    return 0;
}
