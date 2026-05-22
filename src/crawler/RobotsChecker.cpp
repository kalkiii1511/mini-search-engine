#include "crawler/RobotsChecker.hpp"

#include <sstream>

std::string RobotsChecker::extractBaseURL(
    const std::string &url) const
{

    size_t schemePos = url.find("://");

    if (schemePos == std::string::npos)
    {
        return "";
    }

    size_t hostStart = schemePos + 3;
    size_t hostEnd = url.find('/', hostStart);

    if (hostEnd == std::string::npos)
    {
        return url;
    }

    return url.substr(0, hostEnd);
}

bool RobotsChecker::canCrawl(
    const std::string &url) const
{

    std::string baseURL = extractBaseURL(url);

    if (baseURL.empty())
    {
        return false;
    }

    std::string robotsURL =
        baseURL + "/robots.txt";

    std::string robotsContent;

    try
    {
        robotsContent =
            httpClient.fetch(robotsURL);
    }
    catch (...)
    {
        // if robots.txt missing/unreachable,
        // allow crawl for MVP
        return true;
    }

    size_t pathStart = url.find(
        '/',
        baseURL.length());

    std::string targetPath =
        (pathStart == std::string::npos)
            ? "/"
            : url.substr(pathStart);

    std::istringstream stream(robotsContent);
    std::string line;

    bool appliesToUs = false;

    while (std::getline(stream, line))
    {

        if (line.find("User-agent:") == 0)
        {

            std::string agent =
                line.substr(11);

            appliesToUs =
                (agent.find('*') != std::string::npos);
        }
        else if (
            appliesToUs &&
            line.find("Disallow:") == 0)
        {
            std::string blockedPath =
                line.substr(9);

            if (
                !blockedPath.empty() &&
                targetPath.find(blockedPath) == 0)
            {
                return false;
            }
        }
    }

    return true;
}