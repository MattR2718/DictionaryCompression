#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>

std::tuple<std::string, int, int> compressAll(const std::string& text, const std::map<std::string, uint16_t>& dict);

std::tuple<std::string, int, int> compressWord(const std::string& text, const std::map<std::string, uint16_t>& dict, const std::string w);