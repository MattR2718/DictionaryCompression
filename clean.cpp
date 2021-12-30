#include "clean.h"

//Returns true if not a letter or space
bool notAlpha(char c) { return ((isalpha(c)) || (c == ' ')) ? false : true; }

//Replaces all characters, specified in chars, in text with spaces
void replaceAll(std::string& text, std::string chars){
    for (auto c : chars){
        std::replace(text.begin(), text.end(), c, ' ');
    }
}

std::string cleanTxt(std::string& text){
    //Replace all word splitting punctuation with spaces to split into 2 words
    replaceAll(text, "-'\"’");
    //Remove all characters from text that are not a letter or space
    text.erase(std::remove_if(text.begin(), text.end(), notAlpha), text.end());
    //Replace any groups of 2 or more spaces with a single space
    text = std::regex_replace(text, std::regex("\\s{2,}"), " ");
    //Remove excess space at end of text
    if (text[text.length() - 1] == ' ') {text.erase(text.size() - 1);}
    if (text[0] == ' ') {text.erase(text.begin());}

    return text;
}