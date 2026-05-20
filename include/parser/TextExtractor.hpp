#ifndef TEXTEXTRACTOR_HPP
#define TEXTEXTRACTOR_HPP

#include <string>
#include "parser/DOMTree.hpp"

class TextExtractor{
private:
    void bfs(const DOMTree* root,std::string& result);
public:
    std::string extractText(const DOMTree* root);

};


#endif