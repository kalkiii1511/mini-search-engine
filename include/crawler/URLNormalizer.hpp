#ifndef URLNORMALIZER_HPP
#define URLNORMALIZER_HPP

#include <string>

class URLNormalizer {
public:
    std::string normalize(const std::string& url) const;
};
#endif