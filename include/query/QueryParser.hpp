#ifndef QUERYPARSER_HPP
#define QUERYPARSER_HPP

#include <string>
#include <vector>

#include "parser/Tokenizer.hpp"
#include "indexing/stemmer.hpp"
#include "indexing/stopWordRemover.hpp"

class QueryParser {
private:
    Tokenizer tokenizer;
    Stemmer stemmer;
    stopWordRemover stopwordremover;

public:
    std::vector<std::string> parse(const std::string& query) const;
};

#endif