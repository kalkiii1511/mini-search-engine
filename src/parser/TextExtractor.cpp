#include "parser/TextExtractor.hpp"

#include <queue>

void TextExtractor::bfs(const DOMTree *root, std::string &result){
    if(!root || !root->getRoot()) return;
    std::queue<DOMNode*> q;
    q.push(root->getRoot());
    while(!q.empty()){
        DOMNode* node=q.front();
        q.pop();
        if(node->getTagName()!="script" && node->getTagName()!="style"){
            if(!node->getText().empty()){
                result+=node->getText();
                result+=" ";
            }
        }

        const auto& children=node->getChildren();
        
        for(DOMNode* child : children){
            q.push(child);
        }
    }
}

std::string TextExtractor::extractText(const DOMTree* root){
    std::string result="";
    bfs(root,result);

    return result;

}
