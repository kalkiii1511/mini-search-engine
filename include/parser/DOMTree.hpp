#ifndef DOMTREE_HPP
#define DOMTREE_HPP

#include "parser/DOMNode.hpp"

class DOMTree {
private:
    DOMNode* root;
public:
    DOMTree(DOMNode* root);
    DOMNode* getRoot() const;
};

#endif