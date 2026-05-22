#ifndef DOCUMENTSTORAGE_HPP
#define DOCUMENTSTORAGE_HPP

#include "core/document.hpp"

class DocumentStorage {
public:
    virtual void saveDocument(const Document& doc) = 0;
    virtual Document loadDocument(int docId) const = 0;
    virtual void deleteDocument(int docId) = 0;
    virtual ~DocumentStorage() = default;
};

#endif