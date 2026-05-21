#ifndef SEARCHRESULT_HPP
#define SEARCHRESULT_HPP

class SearchResult {
private:
    int docId;
    double score;

public:
    SearchResult(int docId,double score);

    int getId() const;
    double getScore() const;

};

#endif