#include "compress.h"
#include "clean.h"

//Returns vector of either all words in string, or all unique words in string
std::vector<std::string> getWords(std::string text, bool all = false){
    text = cleanTxt(text);

    std::istringstream iss(text);
    std::vector<std::string> words(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    if (all) { return words; }

    std::vector<std::string> unique = {};
    for(auto& w : words){
        if (std::find(unique.begin(), unique.end(), w) == unique.end()){
            unique.push_back(w);
        }
    }

    return unique;
}

//Returns the completely compressed text, the number of compressed words (nums) and the number of punctuation (chars)
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

//Initial idea
//Take entire text and compress every occurrence of first word, then every occurrence of second word
//Does not produce a sensible/single break even point
std::vector<std::tuple<int, int, int>> calcSizesAll(const std::string& text){
    //std::cout<<text<<'\n';
    std::vector<std::string> words = getWords(text);
    std::vector<std::string> used = {""};
    std::vector<std::tuple<int, int, int>> sizes;
    int compressedSize = text.length();
    int dictSize = 0;
    int c = 0;
    std::ofstream file("../sizes.txt");
    for(auto& word : words){
        used.push_back(word);
        dictSize += word.length() + 4;
        int occur = 0;
        for (int i = 0; i < text.length(); i++){
            if (isalpha(text[i])){
                std::string w = "";
                while (isalpha(text[i])){
                    w += text[i];
                    i++;
                }
                i--;
                if (w == word){
                    occur++;
                    compressedSize -= w.length();
                    compressedSize += 2; 
                }
            }
        }
        c++;
        //std::cout<< "Total Size: " << compressedSize + dictSize << "    Compressed Size: " << compressedSize << "    Dict Size: " << dictSize << "    Word: " << word << "   No. Word: " << occur << '\n';
        sizes.push_back(std::make_tuple(0, text.length(), compressedSize + dictSize));
        file << std::get<1>(sizes[c-1]) << ' ' << std::get<2>(sizes[c-1]) << ' ' << used[c] << '\n';
    }
    return sizes;
}

//Compress text word by word
//e.g compress first word, then first and second word ...
//Produces a break even point in second text as compressed size only increases by 2 bytes every word as all words are in dictionary
//whereas total text size increases by the size of each word, majority of which are greater than 2 bytes
std::vector<std::pair<int, int>> calcSizes(const std::string& text){
    std::vector<std::string> used = {""};
    int dictSize = 0;
    int compressedSize = 0;
    std::vector<std::pair<int, int>> sizes;
    std::ofstream file("../sizes.txt");
    for(int i = 0; i < text.length(); i++){
        std::string word = "";
        if (!isalpha(text[i])){
            compressedSize++;
            //if (static_cast<int>(text[i]) < 128) { word += text[i]; } else { word = "'";}
            word += "_";
            //std::cout<<static_cast<int>(text[i])<<'\n';
        }else{
            while(isalpha(text[i])){
                word += text[i];
                i++;
            }
            i--;
            if (std::find(used.begin(), used.end(), word) == used.end()){
                used.push_back(word);
                dictSize += word.length() + 4;
            }
            compressedSize += 2;
        }
        sizes.push_back(std::make_pair(i, compressedSize + dictSize));
        file << i << ' ' << compressedSize+dictSize << ' ' << word << '\n';
    }

    return sizes;
}

//Calculates the break even point where the compressed size becomes less than the size of the original text
void getBreakEven(const std::vector<std::pair<int, int>>& sizes, const std::string& text){
    bool found = false;
    for (auto& p : sizes){
        if (p.first > p.second){
            std::cout<<"Break Even Point: " << p.first << " Characters into text\n";
            std::cout<<"Text At Break Even Point: ";
            for (int i = p.first - 10; i < p.first + 11; i++){
                if ((i > 0) && (i < text.length())){
                    std::cout<<text[i];
                }
            }
            std::cout<<'\n';
            return;
        }
    }
    std::cout<<"NO BREAK EVEN POINT FOUND\n";
}