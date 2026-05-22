#ifndef FILEDOCUMENTSTORAGE_HPP
#define FILEDOCUMENTSTORAGE_HPP

#include "storage/DocumentStorage.hpp"
#include <string>

class FileDocumentStorage : public DocumentStorage {
private:
    static constexpr const char* BASE_PATH = "data/Documents/";

public:
    void saveDocument(const Document& doc) override;
    Document loadDocument(int docId) const override;
    void deleteDocument(int docId) override;
};

#endif