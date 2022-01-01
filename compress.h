#ifndef COMPRESS_H
#define COMPRESS_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <iterator>

std::tuple<std::string, int, int> compressAll(const std::string& text, const std::map<std::string, uint16_t>& dict);

std::vector<std::tuple<int, int, int>> calcSizesAll(const std::string& text);

std::vector<std::pair<int, int>> calcSizes(const std::string& text);

void getBreakEven(const std::vector<std::pair<int, int>>& sizes, const std::string& text);

#endif