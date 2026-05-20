#include "indexing/Indexer.hpp"

void Indexer::addDocument(const Document &doc){
    int id = doc.getId();
    const std::string& text = doc.getExtractedText();
    std::vector<std::string> words = tokenizer.tokenize(text);

    std::vector<std::string> filtered = stopwordremover.remove(words);
    std::vector<std::string> stemmedwords = stemmer.stemWords(filtered);

    for(const std::string& word : stemmedwords){
        invertedIndex.addTerm(word,id);
    }
}

const PostingList* Indexer::search(const std::string &term) const{
    std::string word = stemmer.stem(term);
    return invertedIndex.search(word);
}
