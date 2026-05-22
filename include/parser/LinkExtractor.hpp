#ifndef LINKEXTRACTOR_HPP
#define LINKEXTRACTOR_HPP

#include <vector>
#include <string>

#include "parser/DOMNode.hpp"

class LinkExtractor {
private:
    void traverse(const DOMNode *node,std::vector<std::string> &links) const;

public:
    std::vector<std::string> extractLinks(const DOMNode *root) const;
    
};

#endif