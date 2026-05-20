#include "core/document.hpp"

Document::Document(int DocID, const std::string& URL,const std::string& rawHTML){
    this->docId= DocID;
    this->url = URL;
    this->rawHtml = rawHTML;
}

int Document::getId() const{
    return docId;
}

std::string Document::getURL() const{
    return url;
}

std::string Document::getRawHTML() const{
    return rawHtml;
}

std::string Document::getExtractedText() const{
    return extractedText;
}

void Document::setExtractedText(const std::string& text){
    extractedText = text;
}