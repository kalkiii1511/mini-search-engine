#include "query/QueryParser.hpp"

std::vector<std::string> QueryParser::parse(const std::string &query) const{
    std::vector<std::string> tokens = tokenizer.tokenize(query);
    tokens = stopwordremover.remove(tokens);
    tokens = stemmer.stemWords(tokens);

    return tokens;
}
