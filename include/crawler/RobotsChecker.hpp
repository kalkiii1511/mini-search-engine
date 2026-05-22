#ifndef ROBOTSCHECKER_HPP
#define ROBOTSCHECKER_HPP

#include "crawler/HTTPClient.hpp"

class RobotsChecker {
private:
    HTTPClient httpClient;
    std::string extractBaseURL(const std::string& url) const;
public:
    bool canCrawl(const std::string& url) const;
};

#endif