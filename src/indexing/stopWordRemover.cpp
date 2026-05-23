#include "indexing/stopWordRemover.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> stopWordRemover::remove(const std::vector<std::string> &words) const{
    std::vector<std::string> filtered;
    for(const auto& word : words){
        if(stopWords.find(word) == stopWords.end()){
            filtered.push_back(word);
        }
    }

    return filtered;
}

stopWordRemover::stopWordRemover(){
    std::ifstream file("data/stopWords.txt");
    if (!file.is_open()) {
        file.open("../data/stopWords.txt");
    }

    if(!file.is_open()){
        std::cout << "there is an error in opening the file stopWords.txt" <<std::endl;
        return;
    } 

    std::string word;
    while(file >> word){
        stopWords.insert(word);
    }

}
