#include "storage/FileDocumentStorage.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdio>

void FileDocumentStorage::saveDocument(const Document &doc){
    std::string filePath = std::string(BASE_PATH) + std::to_string(doc.getId())+ ".txt";
    std::ofstream out(filePath);
    if(!out){
        throw std::runtime_error( "failed to open file for writing" );
    }

    out << "docId: " << doc.getId() << "\n";
    out << "url: " << doc.getURL() << "\n";
    out << "===RAW===\n";
    out << doc.getRawHTML() << "\n";
    out << "===TEXT===\n";
    out << doc.getExtractedText();

}

Document FileDocumentStorage::loadDocument(int docId) const{
    std::string filePath =BASE_PATH +std::to_string(docId) + ".txt";
    std::ifstream in(filePath);
    if (!in){
        throw std::runtime_error("Failed to open file for reading");
    }

    std::string docIdLine;
    std::getline(in, docIdLine);

    std::string urlLine;
    std::getline(in, urlLine);

    std::string url = urlLine.substr(5);

    std::string line;
    std::stringstream rawHtml;
    std::stringstream extractedText;

    bool readingRaw = false;
    bool readingText = false;

    while (std::getline(in, line)){
        if (line == "===RAW==="){
            readingRaw = true;
            readingText = false;
            continue;
        }

        if (line == "===TEXT==="){
            readingRaw = false;
            readingText = true;
            continue;
        }

        if (readingRaw){
            rawHtml << line << "\n";
        }

        if (readingText){
            extractedText << line << "\n";
        }
    }

    Document doc(docId, url, rawHtml.str());
    doc.setExtractedText(extractedText.str());

    return doc;
}

void FileDocumentStorage::deleteDocument(int docId)
{
    std::string filePath =
        std::string(BASE_PATH) +
        std::to_string(docId) +
        ".txt";

    std::remove(filePath.c_str());
}
