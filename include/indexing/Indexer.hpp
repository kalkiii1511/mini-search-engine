#ifndef INDEXER_HPP
#define INDEXER_HPP

#include "parser/Tokenizer.hpp"
#include "indexing/InvertedIndex.hpp"
#include "indexing/stemmer.hpp"
#include "indexing/stopWordRemover.hpp"
#include "core/document.hpp"

class Indexer {
private:
    Tokenizer tokenizer;
    InvertedIndex invertedIndex;
    Stemmer stemmer;
    stopWordRemover stopwordremover;

public:
    void addDocument(const Document& doc);
    const PostingList* search(const std::string& term) const;
};

#endif