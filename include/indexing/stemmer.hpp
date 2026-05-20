#ifndef STEMMER_HPP
#define STEMMER_HPP

#include <string>
#include <vector>
class Stemmer {
public:
    std::vector<std::string> stemWords(const std::vector<std::string>& words) const;
    std::string stem(const std::string &word) const;
};

#endif