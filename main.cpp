#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>

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

std::tuple<std::string, int, int> compressAll(const std::string& text, std::map<std::string, uint16_t>& dict){
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
            outText += std::to_string(dict[word]);
            nums++;
        }
        else {
            outText += text[i];
            chars++;
        }
    }
    return std::make_tuple(outText, nums, chars);
}

void writeToFile(const std::string& text, const std::string name){
    std::ofstream file(name);
    file << text;
}

int main() {
    //Open file and place into single string
    std::ifstream file("mbd.txt");
    std::string linetxt;
    std::string text = "";
    while(std::getline(file, linetxt)){
        text += linetxt + " ";
    }
    text.erase(text.length() - 1);

    //text = "Entering that gable-ended Spouter-Inn, you found yourself in a wide, low in in artist’s";

    std::string original = text;

    //text += " " + text;

    //Step 1 - remove punctuation
    //Replace all word splitting punctuation with spaces to split into 2 words
    replaceAll(text, "-'\"’");
    //Remove all characters from text that are not a letter or space
    text.erase(std::remove_if(text.begin(), text.end(), notAlpha), text.end());
    //Replace any groups of 2 or more spaces with a single space
    text = std::regex_replace(text, std::regex("\\s{2,}"), " ");
    
    writeToFile(text, "../out.txt");

    //Step 2 - create dictionary
    //Make dictionary of all unique words
    std::map<std::string, uint16_t> dict = makeDict(text);
    //printDict(dict);

    //Step 3 - calculate size of original text and dictionary
    std::cout<<"Original Text Size: "<<text.length()<<" bytes\n";
    int dictionarySize = calcDictSize(dict);
    std::cout<<"Dictionary Size: "<<dictionarySize<<" bytes\n";

    //Step 4 - fully compress and calculate size
    std::tuple<std::string, int, int> compressedText = compressAll(original, dict);
    //Calculate compressed text size, 2 bytes per number referencing dictionary, 1 byte per punctuation/space
    int compressedSize = (std::get<1>(compressedText) * 2) + std::get<2>(compressedText);
    std::cout<<"Fully Compressed Text Size: " << compressedSize << " bytes\n";
    std::cout<<"Total Compressed Size: "<<dictionarySize+compressedSize<<" bytes\n";

    //Step 5 - find break even point

}
