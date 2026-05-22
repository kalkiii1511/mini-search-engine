#include "crawler/HTTPClient.hpp"

#include <curl/curl.h>
#include <stdexcept>

static size_t WriteCallback(void *contents,size_t size,size_t nmemb,void *userp){
    size_t totalSize = size * nmemb;

    std::string *response = static_cast<std::string *>(userp);
    response->append(static_cast<char *>(contents),totalSize);

    return totalSize;
}

std::string HTTPClient::fetch(const std::string& url) const{
    CURL* curl = curl_easy_init();
    if(!curl){
        throw std::runtime_error("failed to open curl");
    }

    std::string response;

    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION, 1L);
    CURLcode res = curl_easy_perform(curl);
    if(res!=CURLE_OK){
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);

    return response;
}