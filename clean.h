#ifndef CLEAN_H
#define CLEAN_H

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

bool notAlpha(char c);

void replaceAll(std::string& text, std::string chars);

std::string cleanTxt(std::string& text);

#endif