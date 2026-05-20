#include "indexing/stemmer.hpp"

std::string Stemmer::stem(const std::string &word) const{
    int n=word.size();
    if(n>5 && word.substr(n-3) == "ing") return word.substr(0,n-3);
    if(n>4 && (word.substr(n-2) == "ed" || word.substr(n-2) == "ly")) return word.substr(0,n-2);
    if(n>4 && word.back() == 's') return word.substr(0,n-1);

    return word;
}

std::vector<std::string> Stemmer::stemWords(const std::vector<std::string> &words) const{
    std::vector<std::string> stemmedWords;
    stemmedWords.reserve(words.size());
    for(const auto& word : words){
        stemmedWords.push_back(stem(word));
    }
    return stemmedWords;
}
