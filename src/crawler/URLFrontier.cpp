#include "crawler/URLFrontier.hpp"
#include <stdexcept>

void URLFrontier::addURL(const std::string &url){
    if (visited.count(url)){
        return;
    }

    visited.insert(url);
    pending.push(url);
}

bool URLFrontier::hasNext() const{
    return !pending.empty();
}

std::string URLFrontier::getNext(){
    if (pending.empty()){
        throw std::runtime_error("No URLs in frontier");
    }

    std::string next = pending.front();
    pending.pop();

    return next;
}

bool URLFrontier::isVisited(const std::string &url) const{
    return visited.count(url);
}