# Mini Search Engine in C++

A small modular C++ search engine for learning crawling, parsing, indexing, query processing, and ranking.

The current executable reads seed URLs from `data/seeds.txt`, crawls those pages, extracts text from the HTML, saves the documents under `data/Documents/`, builds an inverted index, and searches it from the terminal using TF-IDF scoring.

## Features

- Parses simple HTML into a DOM tree
- Extracts visible text from parsed HTML
- Tokenizes and normalizes text
- Removes stop words from documents and queries
- Applies a simple stemmer
- Builds an inverted index from terms to document postings
- Ranks results with TF-IDF
- Includes crawler, storage, parser, indexing, query, and ranking modules

## Project Structure

```text
.
├── CMakeLists.txt
├── data/
│   ├── seeds.txt
│   └── stopWords.txt
├── include/
│   ├── core/
│   ├── crawler/
│   ├── indexing/
│   ├── parser/
│   ├── query/
│   ├── ranking/
│   └── storage/
├── src/
│   ├── core/
│   ├── crawler/
│   ├── indexing/
│   ├── parser/
│   ├── query/
│   ├── ranking/
│   ├── storage/
│   └── main.cpp
├── tests/
│   ├── crawler/
│   ├── indexing/
│   ├── parser/
│   ├── query/
│   ├── ranking/
│   └── storage/
└── MVP-model.cpp
```

`MVP-model.cpp` is the older single-file prototype. The CMake build uses the modular code under `include/` and `src/`.

## Core Flow

```text
HTML Document
    |
    v
HTMLParser + TextExtractor
    |
    v
SearchEngine
    |
    v
Indexer + InvertedIndex
    |
    v
QueryProcessor
    |
    v
TFIDFRanker
    |
    v
SearchResult list
```

## Important Classes

- `Document`: stores document ID, URL, raw HTML, and extracted text.
- `SearchEngine`: coordinates document preparation, indexing, query processing, and result lookup.
- `HTMLParser`: parses simple HTML into a `DOMTree`.
- `TextExtractor`: extracts searchable text from a `DOMTree`.
- `Tokenizer`: converts text into lowercase terms.
- `stopWordRemover`: removes common terms loaded from `data/stopWords.txt`.
- `Indexer`: tokenizes, filters, stems, and inserts terms into the inverted index.
- `QueryProcessor`: parses queries and gathers posting lists.
- `TFIDFRanker`: scores and sorts matching documents.

## Requirements

- C++17-compatible compiler
- CMake 3.16 or newer
- libcurl development package, because the crawler module uses curl

## Build

```bash
cmake -S . -B build
cmake --build build
```

Or configure, build, and start the program with one command:

```bash
./run.sh
```

## Test

```bash
cmake --build build --target search_engine_tests
ctest --test-dir build --output-on-failure
```

To configure, build, and run the test program with one command:

```bash
./run_tests.sh
```

The test tree is organized by module:

```text
tests/
├── parser/
│   ├── ParserTests.cpp
│   └── HTMLParserTests.cpp
├── indexing/
│   ├── IndexerTests.cpp
│   └── StemmerTests.cpp
├── query/
│   └── QueryProcessorTests.cpp
├── ranking/
│   └── RankerTests.cpp
├── crawler/
│   └── CrawlerTests.cpp
└── storage/
    └── StorageTests.cpp
```

## Run

Add one seed URL per line:

```text
https://example.com
https://example.org
```

Then run from the repository root so the app can find `data/seeds.txt` and `data/stopWords.txt`:

```bash
./build/search_engine
```

You can also pass a different seed file:

```bash
./build/search_engine /path/to/seeds.txt
# or
./run.sh /path/to/seeds.txt
```

Example:

```text
Crawled and indexed documents: 2
Enter query (type exit to quit): example domain
Doc ID: 1 Score: 1 URL: https://example.com
Enter query (type exit to quit): exit
```

## Current Notes

- `SearchEngine` lives in `include/core/SearchEngine.hpp` and `src/core/SearchEngine.cpp`.
- If a document has raw HTML but no extracted text, `SearchEngine::addDocument()` parses the HTML and extracts text before indexing.
- `SearchEngine::crawlFromSeeds()` creates a crawler, loads URLs from `data/seeds.txt`, and indexes each successfully crawled page.
- `HTMLParser` is intentionally basic and will not handle every real-world HTML edge case yet.

## Limitations

- No phrase search
- No boolean query operators
- No persistent index
- Simple stemming only
- Basic HTML parser
- Lightweight assert-based tests instead of a full test framework
