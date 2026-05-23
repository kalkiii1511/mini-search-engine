#include "crawler/crawler.hpp"
#include "core/document.hpp"

#include <fstream>
#include <stdexcept>

Crawler::Crawler(
    Indexer &indexer,
    DocumentStorage &storage,
    const Config &config)
    : indexer(indexer),
      storage(storage),
      config(config),
      nextDocId(1)
{
}

void Crawler::addSeedURL(const std::string &url)
{
    std::string normalized =
        normalizer.normalize(url);

    if (!normalized.empty())
    {
        frontier.addURL(normalized);
    }
}

void Crawler::loadSeedURLs(
    const std::string &filePath)
{
    std::ifstream in(filePath);

    if (!in)
    {
        throw std::runtime_error(
            "Failed to open seed file");
    }

    std::string url;

    while (std::getline(in, url))
    {
        if (url.empty())
        {
            continue;
        }

        addSeedURL(url);
    }
}

int Crawler::crawl()
{

    int crawledPages = 0;

    while (
        frontier.hasNext() &&
        crawledPages < config.maxPages)
    {
        std::string url =
            frontier.getNext();

        if (!robotsChecker.canCrawl(url))
        {
            continue;
        }

        std::string html;

        try
        {
            html = httpClient.fetch(url);
        }
        catch (...)
        {
            continue;
        }

        DOMTree domTree =
            htmlParser.parse(html);

        DOMNode *root =
            domTree.getRoot();

        if (!root)
        {
            continue;
        }

        std::string extractedText =
            textExtractor.extractText(&domTree);

        Document doc(
            nextDocId++,
            url,
            html);

        doc.setExtractedText(extractedText);

        storage.saveDocument(doc);

        indexer.addDocument(doc);

        std::vector<std::string> links =
            linkExtractor.extractLinks(root);

        for (const auto &link : links)
        {

            std::string normalizedLink =
                normalizer.normalize(link);

            if (!normalizedLink.empty())
            {
                frontier.addURL(normalizedLink);
            }
        }

        crawledPages++;
    }

    return crawledPages;
}
