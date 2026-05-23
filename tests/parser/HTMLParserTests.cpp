#include <cassert>
#include <string>

#include "parser/HTMLParser.hpp"
#include "parser/LinkExtractor.hpp"
#include "parser/TextExtractor.hpp"

void runHTMLParserTests() {
    HTMLParser parser;
    DOMTree tree = parser.parse(
        "<html><body><a href=\"https://example.com\">Apple</a>"
        "<p>Search text</p></body></html>");

    DOMNode* root = tree.getRoot();
    assert(root != nullptr);
    assert(root->getTagName() == "html");
    assert(root->getChildren().size() == 1);

    TextExtractor textExtractor;
    std::string text = textExtractor.extractText(&tree);
    assert(text.find("Apple") != std::string::npos);
    assert(text.find("Search text") != std::string::npos);

    LinkExtractor linkExtractor;
    std::vector<std::string> links = linkExtractor.extractLinks(root);
    assert(links.size() == 1);
    assert(links[0] == "https://example.com");
}
