#ifndef URLFRONTIER_HPP
#define URLFRONTIER_HPP

#include <queue>
#include <unordered_set>
#include <string>

class URLFrontier {
private:
    std::queue<std::string> pending;
    std::unordered_set<std::string> visited;

public:
    void addURL(const std::string& url);
    bool hasNext() const;
    std::string getNext();
    bool isVisited(const std::string& url) const;
};

#endif