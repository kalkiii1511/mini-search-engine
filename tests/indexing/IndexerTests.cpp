#include <cassert>

#include "core/document.hpp"
#include "indexing/Indexer.hpp"

void runIndexerTests() {
    Indexer indexer;

    Document doc(1, "memory://doc", "");
    doc.setExtractedText("Apple apple running");
    indexer.addDocument(doc);

    const PostingList* apple = indexer.search("apple");
    assert(apple != nullptr);
    assert(apple->getPostings().at(1) == 2);

    const PostingList* running = indexer.search("running");
    assert(running != nullptr);
    assert(running->getPostings().at(1) == 1);
}
