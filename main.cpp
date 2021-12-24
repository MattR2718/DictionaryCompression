#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

//Returns true if not a letter or space
bool notAlpha(char c) { return ((isalpha(c)) || (c == ' ')) ? false : true; }

//Replaces all characters, specified in chars, in text with spaces
void replaceAll(std::string& text, std::string chars){
    for (auto c : chars){
        std::replace(text.begin(), text.end(), c, ' ');
    }
}

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

std::string compressAll(const std::string& text, std::map<std::string, uint16_t>& dict){
    std::string out = "";
    for (int i = 0; i < text.length(); i++){
        if (isalpha(text[i])) { 
            int j = 0;
            std::string word = "";
            while (isalpha(text[i+j])){
                word += text[i+j];
                j++;
            }
            i += (j - 1);
            out += std::to_string(dict[word]);
        }
        else {
            out += text[i];
        }
    }
    return out;
}

int main() {
    //Open file and place into single string
    std::ifstream file("mbd.txt");
    std::string linetxt;
    std::string text = "";
    while(std::getline(file, linetxt)){
        text += linetxt;
    }

    //text = "Entering that gable-ended Spouter-Inn, you found yourself in a wide, low in in artist’s";

    std::string original = text;

    //Step 1 - remove punctuation
    //std::string parsedText = removePunct(text);
    //Replace all word splitting punctuation with spaces to split into 2 words
    replaceAll(text, "-'\"’");
    //Remove all characters from text that are not a letter leaving just words
    text.erase(std::remove_if(text.begin(), text.end(), notAlpha), text.end());
    //std::cout<<text<<'\n';

    //Step 2 - create dictionary
    //Make dictionary of all unique words
    std::map<std::string, uint16_t> dict = makeDict(text);
    //printDict(dict);

    //Step 3 - calculate size of original text and dictionary
    int dictionarySize = calcDictSize(dict);
    std::cout<<"Dictionary Size: "<<dictionarySize<<" bytes\n";
    std::cout<<"Text Size : "<<text.length()<<" bytes\n";

    //Step 4 - fully compress and calculate size
    std::string compressedText = compressAll(original, dict);
    std::cout<<"Fully Compressed Text Size: " << compressedText.length() << " bytes\n";
    std::cout<<"Total Compressed Size: "<<dictionarySize+compressedText.length()<<" bytes\n";

    //std::cout<<compressedText<<'\n';

    //Step 5

}
