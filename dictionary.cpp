#include "dictionary.h"

//Return whether a given element is in the dictionary
bool inDict(std::map<std::string, uint16_t>& dict, std::string& word){
    for (int i = 0; i < dict.size(); i++){
        if (dict[word] == i) { return true; }
    }
    return false;
}

//Make dictionary of all unique words in given string
std::map<std::string, uint16_t> makeDict(std::string& text){
    std::string word = "";
    std::map<std::string, uint16_t> dict;
    for (int i = 0; i < text.length(); i++){
        if (isalpha(text[i])){
            word += text[i];
        } else if (!word.empty()){
            if (dict.find(word) == dict.end()){
                dict[word] = dict.size();
            }
            word = "";
        }
    }
    dict[word] = dict.size();
    return dict;
}

//Prints keys and elements from dictionary
void printDict(std::map<std::string, uint16_t>& dict){
    std::cout<<"------------------\n";
    std::cout<<"DICTIONARY:\n";
    for (auto entry : dict){
        std::cout<<"Key: "<<entry.first<<"     Element: "<<int(entry.second)<<'\n';
    }
    std::cout<<"------------------\n";
}

int calcDictSize(std::map<std::string, uint16_t>& dict){
    int letterSum = 0;
    for (auto& w : dict){ letterSum += w.first.length(); }
    int extra = dict.size() * 4;
    return letterSum+extra;
}