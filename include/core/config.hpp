#ifndef CONFIG_HPP
#define CONFIG_HPP

class Config
{
public:
    int maxPages;
    int maxCrawlDepth;

    Config(
        int maxPages = 100,
        int maxCrawlDepth = 3)
        : maxPages(maxPages),
          maxCrawlDepth(maxCrawlDepth)
    {
    }
};

#endif