#include "compress.h"

std::tuple<std::string, int, int> compressAll(const std::string& text, const std::map<std::string, uint16_t>& dict){
    std::string outText = "";
    int nums = 0;
    int chars = 0;
    for (int i = 0; i < text.length(); i++){
        if (isalpha(text[i])) { 
            int j = 0;
            std::string word = "";
            while (isalpha(text[i+j])){
                word += text[i+j];
                j++;
            }
            i += (j - 1);
            //std::cout<<word<<'\n';
            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << dict.at(word);
            outText += ss.str();
            nums++;
        }
        else {
            outText += text[i];
            chars++;
        }
    }
    return std::make_tuple(outText, nums, chars);
}

//SORT OUT WAY OF COMPRESSING WORD BY WORD

std::tuple<std::string, int, int> compressWord(const std::string& text, const std::map<std::string, uint16_t>& dict, const std::string w){
    std::string outText = "";
    std::string word = "";
    int nums = 0;
    int chars = 0;
    for (int i = 0; i < text.length(); i++){
        if (text[i] == ' '){
            if (dict.at(word) )
            outText += word;
        } else {
            word += text[i];
        }
    }
}

//ADD IN CALCULATING COMPRESSION WITHOUT ACTUALLY COMPRESSING