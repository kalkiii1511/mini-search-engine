#include <cassert>

#include "indexing/stemmer.hpp"

void runStemmerTests() {
    Stemmer stemmer;

    assert(stemmer.stem("running") == "runn");
    assert(stemmer.stem("tested") == "test");
    assert(stemmer.stem("quickly") == "quick");
    assert(stemmer.stem("apples") == "apple");
    assert(stemmer.stem("cat") == "cat");
}
