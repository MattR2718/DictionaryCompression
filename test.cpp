#include <iostream>
#include <vector>
#include <map>
#include <gtest/gtest.h>

#include "clean.h"
#include "compress.h"
#include "dictionary.h"

TEST(TrueTest, AlwaysTrue){
    EXPECT_EQ(1, 1);
}

TEST(Clean, GivenTest){
    std::string testClean = "Entering that gable-ended Spouter-Inn, you found yourself in a wide, low";
    cleanTxt(testClean);
    std::string given = "Entering that gable ended Spouter Inn you found yourself in a wide low";
    EXPECT_EQ(testClean, given);
}

TEST(Clean, MadeTests){
    std::vector<std::string> testCleans = {
        "I found a number of young seamen gathered about a table, examining by a dim light divers specimens of skrimshander. I sought the landlord,",
        ", and on through yon low-arched way- cut through what in old times must have been a great central chimney "
    };
    std::vector<std::string> cleaned = {
        "I found a number of young seamen gathered about a table examining by a dim light divers specimens of skrimshander I sought the landlord",
        "and on through yon low arched way cut through what in old times must have been a great central chimney"
    };
    for (int i = 0; i < testCleans.size(); i++){
        EXPECT_EQ(cleanTxt(testCleans[i]), cleaned[i]);
    }
}

TEST(Dictionary, GivenTest){
    std::map<std::string, uint16_t> givenDict = {{"Entering", 0}, {"that", 1}, {"gable", 2}, {"ended", 3}, {"Spouter", 4}, {"Inn", 5}, {"you", 6}, {"found", 7}};
    std::string makeMap = "Entering that gable ended Spouter Inn you found";
    EXPECT_EQ(makeDict(makeMap), givenDict);
}

TEST(Dictionary, MadeTests){
    std::vector<std::map<std::string, uint16_t>> testDicts = {
        {{"I", 0}, {"found", 1}, {"a", 2}, {"number", 3}, {"of", 4}, {"young", 5}, {"seamen", 6}, {"gathered", 7}, {"about", 8}, {"table", 9}},
        {{"and", 0}, {"on", 1}, {"through", 2}, {"yon", 3}, {"low", 4}, {"arched", 5}, {"way", 6}, {"cut", 7}, {"what", 8}, {"On", 9}}
    };
    std::vector<std::string> makeMaps = {
        "I found a number of young seamen gathered about a table",
        "and on through yon low on arched way cut through what On"
    };
    for (int i = 0; i < testDicts.size(); i++){
        EXPECT_EQ(makeDict(makeMaps[i]), testDicts[i]);
    }
}

TEST(CalcDictSize, GivenTest){
    std::map<std::string, uint16_t> givenDict = {{"Entering", 0}, {"that", 1}, {"gable", 2}, {"ended", 3}, {"Spouter", 4}, {"Inn", 5}, {"you", 6}, {"found", 7}};
    int dictSize = (8 + 4) + (4 + 4) + (5 + 4) + (5 + 4) + (7 + 4) + (3 + 4) + (3 + 4) + (5 + 4);
    EXPECT_EQ(calcDictSize(givenDict), dictSize);
}

TEST(CalcDictSize, MadeTests){
    std::vector<std::map<std::string, uint16_t>> testDicts = {
        {{"I", 0}, {"found", 1}, {"a", 2}, {"number", 3}, {"of", 4}, {"young", 5}, {"seamen", 6}, {"gathered", 7}, {"about", 8}, {"table", 9}},
        {{"and", 0}, {"on", 1}, {"through", 2}, {"yon", 3}, {"low", 4}, {"arched", 5}, {"way", 6}, {"cut", 7}, {"what", 8}, {"On", 9}}
    };
    std::vector<int> dictSizes = {
        (1 + 4) + (5 + 4) + (1 + 4) + (6 + 4) + (2 + 4) + (5 + 4) + (6 + 4) + (8 + 4) + (5 + 4) + (5 + 4),
        (3 + 4) + (2 + 4) + (7 + 4) + (3 + 4) + (3 + 4) + (6 + 4) + (3 + 4) + (3 + 4) + (4 + 4) + (2 + 4)
    };
    for (int i = 0; i < testDicts.size(); i++){
        EXPECT_EQ(calcDictSize(testDicts[i]), dictSizes[i]);
    }
}

TEST(CalcTotalSize, MadeTests){
    std::vector<std::map<std::string, uint16_t>> testDicts = {
        {{"I", 0}, {"found", 1}, {"a", 2}, {"number", 3}, {"of", 4}, {"young", 5}, {"seamen", 6}, {"gathered", 7}, {"about", 8}, {"table", 9}},
        {{"and", 0}, {"on", 1}, {"through", 2}, {"yon", 3}, {"low", 4}, {"arched", 5}, {"way", 6}, {"cut", 7}, {"what", 8}, {"On", 9}}
    };
    std::vector<std::string> texts = {
        "I found a number of young seamen gathered about a table",
        "and on through yon low on arched way cut through what On"
    };
    std::vector<std::tuple<std::string, int, int>> compressedTextSizes = {
        compressAll(texts[0], testDicts[0]),
        compressAll(texts[1], testDicts[1])
    };
    std::vector<int> compressedSizes = {
        22 + 10,
        24 + 11
    };
    for (int i = 0; i < testDicts.size(); i++){
        EXPECT_EQ((std::get<1>(compressedTextSizes[i]) * 2) + std::get<2>(compressedTextSizes[i]), compressedSizes[i]);
    }
}