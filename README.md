Mini Search Engine (C++)

A toy search engine built in C++ to learn object-oriented design, class interactions, and basic information retrieval concepts.

Goal

This project was built to understand C++ OOP by implementing a simplified search engine architecture from scratch.

Concepts practiced:

* Classes and objects
* Encapsulation
* Composition
* References and const correctness
* STL containers (vector, unordered_map, unordered_set)
* Basic ranking logic
* Clean separation of responsibilities

Architecture

User Query
   ↓
QueryProcessor
   ↓
SearchEngine
   ↓
Indexer
   ↓
Search Results

Core components:

Document

Represents a searchable document.

Fields:

* id
* content

Parser

Converts raw text into normalized tokens.

Responsibilities:

* Tokenization
* Lowercasing
* Removing non-alphanumeric separators

Example:

"Apple makes iPhone!!"
→ ["apple", "makes", "iphone"]

Indexer

Builds an inverted index.

Structure:

unordered_map<string, unordered_map<int, int>>

Meaning:

word -> (docId -> frequency)

Example:

"apple" -> {
   1 : 3,
   3 : 1
}

QueryProcessor

Processes user queries using the same normalization logic as documents.

Example:

"APPLE iphone!!!"
→ ["apple", "iphone"]

SearchEngine

Main orchestrator.

Responsibilities:

* Add documents
* Process user queries
* Query index for every token
* Compute document scores
* Return ranked results

Search Strategy

For a multi-word query:

apple iphone

Flow:

1. Query is tokenized
2. Each token is searched in the index
3. Matching document frequencies are accumulated
4. Results are sorted by score descending

Example:

apple:
  doc1 -> 3
  doc2 -> 1
iphone:
  doc1 -> 2
  doc3 -> 4

Combined scores:

doc1 -> 5
doc2 -> 1
doc3 -> 4

Ranked output:

doc1
doc3
doc2

Build

Compile with C++17:

g++ main.cpp -std=c++17 -o search_engine

or

clang++ main.cpp -std=c++17 -o search_engine

Run

./search_engine

Example interaction:

Enter query: apple iphone
Doc ID: 1 Score: 5
Doc ID: 3 Score: 4
Doc ID: 2 Score: 1

Future Improvements

Planned extensions:

* Stop-word removal
* Stemming
* Phrase search
* AND / OR query support
* Persistent storage
* Web crawler
* HTML parser
* Ranker abstraction
* SQLite / RocksDB backend
* Multithreaded crawling

Why this project?

This is intentionally a learning project, not a production search engine.

The focus is understanding system decomposition and writing clean C++ OOP code.