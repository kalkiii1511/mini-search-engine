#include "core/SearchResult.hpp"

SearchResult::SearchResult(int docId, double score){
    this->docId = docId;
    this->score = score;
}

int SearchResult::getId() const{
    return docId;
}

double SearchResult::getScore() const{
    return score;
}
