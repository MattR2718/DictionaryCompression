#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>

std::tuple<std::string, int, int> compressAll(const std::string& text, const std::map<std::string, uint16_t>& dict);

std::tuple<std::string, int, int> compressWord(const std::string& text, const std::map<std::string, uint16_t>& dict, const std::string w);

std::vector<int> calcBreakEven(const std::string& text, const int originalSize);