#ifndef STOPWORDREMOVER_HPP
#define STOPWORDREMOVER_HPP

#include <string>
#include <vector>
#include <unordered_set>

class stopWordRemover {
private:
    std::unordered_set<std::string> stopWords;

public:
    stopWordRemover();
    std::vector<std::string> remove(const std::vector<std::string>& words) const;
};

#endif