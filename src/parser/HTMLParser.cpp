#include "parser/HTMLParser.hpp"
#include <stack>

DOMTree HTMLParser::parse(const std::string& html){
    std::stack<DOMNode*> st;
    DOMNode* root=nullptr;

    int i = 0;
    while(i<html.size()){
        if(html[i]=='<'){
            if(i+1<html.size() && html[i+1]=='/'){
                i+=2;
                while(html[i]!='>'){
                    i++;
                }
                if(!st.empty()){
                    st.pop();
                }
                i++;
            }
            else{
                i++;
                std::string tag;
                while(i<html.size() && html[i]!=' ' && html[i]!='>'){
                    tag+=html[i];
                    i++;
                }
                DOMNode* node = new DOMNode(tag);
                if(st.empty()) root=node;
                else{
                    st.top()->addChild(node);
                }
                while(i<html.size() && html[i]!='>'){
                    while(i<html.size() && html[i]==' ') i++;
                    if(html[i]=='>') break;
                    std::string key="";
                    while(i<html.size() && html[i]!='='){
                        key+=html[i];
                        i++;
                    }
                    i++;
                    if(i<html.size() && html[i]=='"') i++;
                    std::string value="";
                    while(i<html.size() && html[i]!='"'){
                        value+=html[i];
                        i++;
                    }
                    if(i<html.size() && html[i]=='"') i++;

                    node->addAttribute(key,value);

                }

                st.push(node);
                i++;
            }
        }

        else{
            std::string text;
            while(i<html.size() && html[i]!='<'){
                text+=html[i];
                i++;
            }
            if(!st.empty() && !text.empty()){
                st.top()->setText(text);
            }
        }
    }

    return DOMTree(root);
}