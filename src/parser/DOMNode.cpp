#include "parser/DOMNode.hpp"

DOMNode::DOMNode(const std::string& tag){
    tagName=tag;
}

void DOMNode::addChild(DOMNode* child){
    children.push_back(child);
}

void DOMNode::setText(const std::string &content){
    text=content;
}

void DOMNode::addAttribute(const std::string &key, const std::string &value){
    attributes[key]=value;
}

std::string DOMNode::getTagName() const{
    return tagName;
}

std::string DOMNode::getText() const{
    return text;
}

const std::vector<DOMNode*>& DOMNode::getChildren() const{
    return children;
}

std::string DOMNode::getAttribute(const std::string &key) const{
    auto it = attributes.find(key);

    if (it != attributes.end()){
        return it->second;
    }

    return "";
}