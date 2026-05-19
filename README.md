# Mini Search Engine in C++

A small command-line search engine written in C++ for learning object-oriented design and basic information retrieval concepts.

The project indexes a fixed set of in-memory documents, accepts queries from the terminal, and returns matching document IDs ranked by a simple frequency-based score.

## Features

- Tokenizes document text and user queries
- Normalizes text to lowercase
- Treats non-alphanumeric characters as separators
- Builds an inverted index from words to document frequencies
- Removes a small set of stop words from queries
- Scores documents by accumulated term frequency
- Sorts results by score in descending order

## Concepts Practiced

- Classes and objects
- Encapsulation
- Composition
- `const` correctness and references
- STL containers such as `vector`, `unordered_map`, and `unordered_set`
- Basic ranking logic
- Separation of responsibilities between parser, indexer, query processor, and search engine

## Project Structure

```text
.
├── README.md
└── main.cpp
```

## Architecture

```text
User Query
    |
    v
QueryProcessor
    |
    v
SearchEngine
    |
    v
Indexer
    |
    v
Ranked Results
```

### `Document`

Represents one searchable document.

Fields:

- `id`: unique document ID
- `content`: raw document text

### `Parser`

Converts raw text into normalized tokens.

Example:

```text
Apple makes iPhone!!
```

becomes:

```text
["apple", "makes", "iphone"]
```

### `Indexer`

Builds and queries an inverted index.

Internal structure:

```cpp
unordered_map<string, unordered_map<int, int>>
```

Meaning:

```text
word -> (document ID -> frequency)
```

Example:

```text
"apple" -> {
  1: 1,
  3: 1,
  4: 1
}
```

### `QueryProcessor`

Processes user queries using the same parser as documents, then removes stop words.

Current stop words:

```text
the, is, a, an, of, to
```

Example:

```text
APPLE is an iPhone!!!
```

becomes:

```text
["apple", "iphone"]
```

### `SearchEngine`

Coordinates the full search flow.

Responsibilities:

- Add documents to the index
- Process query text
- Search the index for every query token
- Combine scores per document
- Return ranked results

## Search Strategy

For a multi-word query, each token is searched independently. If a document matches multiple query terms, the frequencies are added together.

Example query:

```text
apple iphone
```

Example scores:

```text
apple:
  doc1 -> 1
  doc3 -> 1
  doc4 -> 1

iphone:
  doc1 -> 1
  doc4 -> 1
```

Combined scores:

```text
doc1 -> 2
doc4 -> 2
doc3 -> 1
```

## Requirements

- A C++17-compatible compiler
- `g++` or `clang++`

## Build

Using `g++`:

```bash
g++ main.cpp -std=c++17 -o search_engine
```

Using `clang++`:

```bash
clang++ main.cpp -std=c++17 -o search_engine
```

## Run

```bash
./search_engine
```

Example session:

```text
Enter query (type exit to quit): apple iphone
Doc ID: 1 Score: 2
Doc ID: 4 Score: 2
Doc ID: 3 Score: 1
Enter query (type exit to quit): windows
Doc ID: 2 Score: 1
Enter query (type exit to quit): exit
```

Note: documents with the same score may appear in any order because the index uses `unordered_map`.

## Current Dataset

The demo indexes these documents in `main.cpp`:

```text
1: Apple makes iPhone
2: Microsoft makes Windows
3: Apple sells Macbook
4: iPhone is made by Apple
```

## Limitations

This is a learning project, not a production search engine. Current limitations include:

- Documents are hardcoded in `main.cpp`
- No persistent storage
- No phrase search
- No boolean `AND` / `OR` query operators
- No stemming or lemmatization
- No TF-IDF or advanced ranking
- No web crawling or HTML parsing

## Possible Improvements

- Load documents from files
- Add persistent storage
- Add phrase search
- Add boolean query support
- Implement stemming
- Use TF-IDF or BM25 scoring
- Add a ranker abstraction
- Add tests
- Add a SQLite or RocksDB backend
- Add a crawler and HTML parser

## Purpose

The goal of this project is to understand how a search engine can be decomposed into smaller components while practicing clean C++ OOP design.
