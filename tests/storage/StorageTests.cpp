#include <cassert>
#include <filesystem>

#include "storage/FileDocumentStorage.hpp"

void runStorageTests() {
    std::filesystem::create_directories("data/Documents");

    FileDocumentStorage storage;
    Document doc(9999, "https://example.com", "<html>raw</html>");
    doc.setExtractedText("example text");

    storage.saveDocument(doc);
    Document loaded = storage.loadDocument(9999);

    assert(loaded.getId() == 9999);
    assert(loaded.getURL() == "https://example.com");
    assert(loaded.getRawHTML().find("<html>raw</html>") != std::string::npos);
    assert(loaded.getExtractedText().find("example text") != std::string::npos);

    storage.deleteDocument(9999);
}
