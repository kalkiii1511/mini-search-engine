#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>

class Document{
private:
    int docId;
    std::string url;
    std::string rawHtml;
    std::string extractedText;

public:
    Document(int DocID,const std::string& URL,const std::string& rawHTML);
    int getId() const;
    std::string getURL() const;
    std::string getRawHTML() const;
    std::string getExtractedText() const;

    void setExtractedText(const std::string& text);
};


#endif