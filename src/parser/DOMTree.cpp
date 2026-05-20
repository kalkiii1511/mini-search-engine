#include "parser/DOMTree.hpp"

DOMTree::DOMTree(DOMNode* root){
    this->root=root;
}

DOMNode* DOMTree::getRoot() const{
    return root;
}