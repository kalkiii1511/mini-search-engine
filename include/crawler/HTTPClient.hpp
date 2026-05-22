#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <string>

class HTTPClient {
public:
    std::string fetch(const std::string& url) const;
};

#endif