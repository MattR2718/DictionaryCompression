#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "clean.h"
#include "dictionary.h"
#include "compress.h"

bool strIsNum(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) { ++it; }
    return !s.empty() && it == s.end();
}

std::string keyAtEle(const std::string& ele, const std::map<std::string, uint16_t>& dict){
    //std::cout<<ele<<'\n';
    int num = std::stoi(ele);
    for (auto& e : dict){
        if (e.second == num) { return e.first; }
    }
    throw std::invalid_argument(std::to_string(num) + " is not an element in dict");
    return "ERROR";
}

bool isStrDigit(char c){
    int digit = c - '0';
    if ((digit >= 0) && (digit <=9)) { return true; }
    return false;
}

int countChars(const std::string& text){
    int count = 0;
    for(auto& c : text){
        if (!isdigit(c)) { count++; }
    }
    return count;
}

std::string findWord(const std::map<std::string, uint16_t>& dict, const int i){
    for (auto& e : dict){
        if (e.second == i) { return e.first; }
    }
    throw std::invalid_argument("int i not present in dict");
    return "ERROR";
}

std::string formatFileName(const std::string& word, const std::map<std::string, uint16_t>& dict){
    return "../Compressed/" + word + "-" + std::to_string(dict.at(word)) + ".txt";
}

void writeToFile(const std::string& text, const std::string name, bool writeDict = false, const std::map<std::string, uint16_t>& dict = std::map<std::string, uint16_t>{}, const std::string word = ""){
    std::ofstream file(name);
    file << text << "\n\n";
    if (writeDict){
        for (auto& ke : dict){
            if (ke.second <= dict.at(word)){
                file << ke.first << ", " << ke.second << '\n';
            }
        }
    }
}

int main() {
    //Open file and place into single string
    //DOES NOT KEEP RETURN CHARS
    std::ifstream file("mbd.txt");
    std::string linetxt;
    std::string text = "";
    while(std::getline(file, linetxt)){
        text += linetxt + " ";
    }

    //text = "Entering that gable-ended Spouter-Inn, you found yourself in a wide, low in in artist’s";
    text += " " + text;
    std::string original = text;
    
    //Step 1 - remove punctuation
    cleanTxt(text);
    std::string parsedText = text;

    //Step 2 - create dictionary
    std::map<std::string, uint16_t> dict = makeDict(text);

    //Step 3 - calculate size of original text and dictionary
    std::cout<<"Original Text Size: "<<original.length()<<" bytes\n";
    int dictionarySize = calcDictSize(dict);
    std::cout<<"Dictionary Size: "<<dictionarySize<<" bytes\n";
    
    //Step 4 - fully compress and calculate size
    std::tuple<std::string, int, int> compressedText = compressAll(original, dict);
    //Calculate compressed text size, 2 bytes per number referencing dictionary, 1 byte per punctuation/space
    int compressedSize = (std::get<1>(compressedText) * 2) + std::get<2>(compressedText);
    std::cout<<"Fully Compressed Text Size: " << compressedSize << " bytes\n";
    std::cout<<"Total Compressed Size: "<<dictionarySize+compressedSize<<" bytes\n";
    std::cout<<"Size Difference: " << original.length() - (dictionarySize+compressedSize) <<" bytes\n";

    //Step 5 - find break even point
    //std::vector<std::tuple<int, int, int>> allSizes = calcSizesAll(original);
    std::vector<std::pair<int, int>> sizes = calcSizes(original);
    getBreakEven(sizes, original);
}