#include "crawler/URLNormalizer.hpp"

#include <algorithm>
#include <cctype>

std::string URLNormalizer::normalize(const std::string& url) const {
    std::string normalized = url;

    normalized.erase(
        normalized.begin(),
        std::find_if(
            normalized.begin(),
            normalized.end(),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        )
    );

    normalized.erase(
        std::find_if(
            normalized.rbegin(),
            normalized.rend(),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        ).base(),
        normalized.end()
    );

    size_t fragPos = normalized.find('#');
    if (fragPos != std::string::npos) {
        normalized.erase(fragPos);
    }

    size_t schemePos = normalized.find("://");

    if (schemePos != std::string::npos) {
        std::transform(
            normalized.begin(),
            normalized.begin() + schemePos,
            normalized.begin(),
            [](unsigned char ch) {
                return std::tolower(ch);
            }
        );

        size_t hostStart = schemePos + 3;
        size_t hostEnd = normalized.find('/', hostStart);

        if (hostEnd == std::string::npos) {
            hostEnd = normalized.size();
        }

        std::string hostPort = normalized.substr(hostStart, hostEnd - hostStart);
        size_t colonPos = hostPort.find(':');

        if (colonPos != std::string::npos) {
            std::string host = hostPort.substr(0, colonPos);
            std::string port = hostPort.substr(colonPos + 1);
            std::string scheme = normalized.substr(0, schemePos);

            if ((scheme == "http" && port == "80") ||
                (scheme == "https" && port == "443")) {
                hostPort = host;
            }
        }

        std::transform(
            hostPort.begin(),
            hostPort.end(),
            hostPort.begin(),
            [](unsigned char ch) {
                return std::tolower(ch);
            }
        );

        normalized.replace(hostStart, hostEnd - hostStart, hostPort);
    }

    // remove trailing slash
    if (normalized.size() > 1 && normalized.back() == '/') {
        normalized.pop_back();
    }

    return normalized;
}