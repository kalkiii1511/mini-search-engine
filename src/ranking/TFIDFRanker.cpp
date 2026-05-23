#include "ranking/TFIDFRanker.hpp"

#include <unordered_map>
#include <algorithm>
#include <cmath>

std::vector<SearchResult> TFIDFRanker::rank(
    const std::unordered_map<std::string, int> &queryFreq,
    const std::vector<std::string> &uniqueTerms,
    const std::vector<const PostingList *> &postingLists,
    int totalDocs) const{

    std::unordered_map<int, double> scores;

    for (size_t i = 0; i < uniqueTerms.size(); i++)
    {

        const PostingList *postingList = postingLists[i];

        if (postingList == nullptr)
        {
            continue;
        }

        int df = postingList->getDocumentFrequency();

        if (df == 0)
        {
            continue;
        }

        double idf = std::log(
            (static_cast<double>(totalDocs) + 1.0) /
            (static_cast<double>(df) + 1.0)) + 1.0;

        int qtf = queryFreq.at(uniqueTerms[i]);

        const auto &postings = postingList->getPostings();

        for (const auto &[docId, tf] : postings)
        {
            scores[docId] += qtf * tf * idf;
        }
    }

    std::vector<SearchResult> results;
    results.reserve(scores.size());

    for (const auto &[docId, score] : scores)
    {
        results.push_back(SearchResult(docId, score));
    }

    std::sort(
        results.begin(),
        results.end(),
        [](const SearchResult &a, const SearchResult &b)
        {
            return a.getScore() > b.getScore();
        });

    return results;
}
