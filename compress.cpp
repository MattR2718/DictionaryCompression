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
            if (dict.at(word))
            outText += word;
        } else {
            word += text[i];
        }
    }
}

//ADD IN CALCULATING COMPRESSION WITHOUT ACTUALLY COMPRESSING
std::vector<int> calcBreakEven(const std::string& text, const int originalSize){
    //std::cout<<text<<'\n';
    std::vector<std::string> used = {""};
    std::vector<int> sizes = {};
    int compressedSize = text.length();
    int dictSize = 0;
    int atWord = 0;
    //std::cout<<text.length()<<'\n';
    int c = 0;
    while (atWord < text.length()){
        std::string word = "";
        while ((atWord < text.length()) && (std::find(used.begin(), used.end(), word) != used.end())){
            word = "";
            while ((atWord < text.length()) && (isalpha(text[atWord]))){
                word += text[atWord];
                atWord++;
            }
            atWord ++;
        }
        c++;
        if (word.length() > 0) { 
            used.push_back(word);
            dictSize += word.length() + 4;
            //std::cout<<c << ": " << word<<'\n';
        }
        //std::cout<<dictSize<<'\n';
        for (int i = 0; i < text.length(); i++){
            if (isalpha(text[i])){
                std::string w = "";
                int j = i;
                while (isalpha(text[j])){
                    w += text[j];
                    j++;
                }
                j--;
                if (w == word){
                    compressedSize -= w.length();
                    compressedSize += 2; 
                }
                i = j;
            }
        }
        //std::cout<<word << "  " << compressedSize<<'\n';
        sizes.push_back(compressedSize + dictSize);
    }

    std::ofstream file("../sizes.txt");
    for (int l = 0; l < sizes.size()-1; l++){
        file << l << ' ' << sizes[l] << ' ' << used[l+1] << '\n';
    }

    return sizes;
}