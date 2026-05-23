#ifndef HTMLPARSER_HPP
#define HTMLPARSER_HPP

#include <string>
#include "parser/DOMTree.hpp"

class HTMLParser {
public:
    DOMTree parse(const std::string& html);
};

#endif
