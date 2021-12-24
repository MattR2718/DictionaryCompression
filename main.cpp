#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>
#include <sstream>
#include <iomanip>

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

std::tuple<std::string, int, int> compressWord(const std::string& text, const std::map<std::string, uint16_t>& dict, const std::string w){
    std::string outText = "";
    int nums = 0;
    int chars = 0;
    for (int i = 0; i < text.length(); i++){
        int j = 0;
        std::string word = "";
        if (isalpha(text[i])){ 
            while (isalpha(text[i+j])){
                word += text[i+j];
                j++;
            }
            i += (j - 1);
            //std::cout<<word<<'\n';
            if (word == w) {
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << dict.at(w);
                outText += ss.str();
                nums++;
            } else {
                outText += word;
                chars += word.length();
            }
        } else if (isStrDigit(text[i])){
            while (isStrDigit(text[i+j])){
                word += text[i+j];
                j++;
            }
            std::cout<<word<<'\n';
            i += (j - 1);
            if (word == w) {
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << dict.at(w);
                outText += ss.str();
                nums++;
            } else {
                outText += word;
                chars += keyAtEle(word, dict).length();
            }
        }
        else {
            outText += text[i];
            chars++;
        }
    }
    return std::make_tuple(outText, nums, chars);
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
    std::ifstream file("mbd.txt");
    std::string linetxt;
    std::string text = "";
    while(std::getline(file, linetxt)){
        text += linetxt + " ";
    }

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
    text.erase(text.size() - 1);
    std::string parsedText = text;
    //writeToFile(text, "../out.txt");

    //Step 2 - create dictionary
    //Make dictionary of all unique words
    std::map<std::string, uint16_t> dict = makeDict(text);
    //printDict(dict);
    //writeToFile(text, "../out.txt", true, dict, "obstreperously");
    //std::cout<<text<<'\n';

    //Step 3 - calculate size of original text and dictionary
    std::cout<<"Original Text Size: "<<text.length()<<" bytes\n";
    int dictionarySize = calcDictSize(dict);
    std::cout<<"Dictionary Size: "<<dictionarySize<<" bytes\n";
    
    //Step 4 - fully compress and calculate size
    std::tuple<std::string, int, int> compressedText = compressAll(original, dict);
    //std::cout<<dict.size()<<'\n';
    //Calculate compressed text size, 2 bytes per number referencing dictionary, 1 byte per punctuation/space
    int compressedSize = (std::get<1>(compressedText) * 2) + std::get<2>(compressedText);
    std::cout<<"Fully Compressed Text Size: " << compressedSize << " bytes\n";
    std::cout<<"Total Compressed Size: "<<dictionarySize+compressedSize<<" bytes\n";

    //Step 5 - find break even point
    std::string compressingText = parsedText;
    std::vector<std::pair<std::string, int>> sizes;
    std::map<std::string, uint16_t> currDict;
    int nums = 0;
    int chars = 0;
    for (int i = 0; i < dict.size(); i++){
        std::string compWord = findWord(dict, i);
        compressedText = compressWord(compressingText, dict, compWord);
        nums += std::get<1>(compressedText);
        compressingText = std::get<0>(compressedText);
        chars = countChars(compressingText);
        compressedSize = (nums * 2) + chars;
        //std::cout<<chars<<'\n';
        currDict[compWord] = dict[compWord];
        int currDictionarySize = calcDictSize(currDict);
        sizes.push_back(std::make_pair(compWord, currDictionarySize+compressedSize));
        std::cout<<i<<": "<<compWord<<" - "<<currDictionarySize+compressedSize<<" bytes\n";
        //std::cout<<compressedSize<<'\n';
        writeToFile(compressingText, formatFileName(compWord, dict), true, dict, compWord);
    }
}