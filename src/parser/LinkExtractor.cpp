#include "parser/LinkExtractor.hpp"

#include <queue>
std::vector<std::string> LinkExtractor::extractLinks(const DOMNode *root) const{
    std::vector<std::string> links;
    traverse(root,links);

    return links;
}

void LinkExtractor::traverse(const DOMNode *root,std::vector<std::string> &links) const{
    if (!root) return;

    std::queue<const DOMNode *> visiting;
    visiting.push(root);

    while (!visiting.empty()){
        const DOMNode *node = visiting.front();
        visiting.pop();

        if (node->getTagName() == "a"){
            std::string link = node->getAttribute("href");
            if (!link.empty()){
                links.push_back(link);
            }
        }

        const auto &children = node->getChildren();

        for (const auto &child : children){
            visiting.push(child);
        }
    }
}
