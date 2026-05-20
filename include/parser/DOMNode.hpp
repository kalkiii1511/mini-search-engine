#ifndef DOMNODE_HPP
#define DOMNODE_HPP

#include <string>
#include <vector>
#include <unordered_map>

class DOMNode {
private:
    std::string tagName;
    std::string text="";
    std::unordered_map<std::string, std::string> attributes;
    std::vector<DOMNode *> children;
public:
    DOMNode(const std::string& tag);

    void addChild(DOMNode* child);
    void setText(const std::string& content);
    void addAttribute(const std::string& key,const std::string& value);

    std::string getTagName() const;
    std::string getText() const;
    const std::vector<DOMNode*>& getChildren() const;
    std::string getAttribute(const std::string &key) const;
};

#endif