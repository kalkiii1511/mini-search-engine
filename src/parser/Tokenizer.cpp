#include "parser/Tokenizer.hpp"
#include <cctype>

std::vector<std::string> Tokenizer::tokenize(const std::string &content) const{
    std::vector<std::string> words;
    std::string buffer;
    int i=0;
    while(i<content.size()){
        if(isalnum(content[i])){
            buffer+=tolower(content[i]);
        }
        else{
            if(!buffer.empty()){
                words.push_back(buffer);
                buffer = "";
            }
        }
        i++;
    }

    if(!buffer.empty()) words.push_back(buffer);
    return words;
}
