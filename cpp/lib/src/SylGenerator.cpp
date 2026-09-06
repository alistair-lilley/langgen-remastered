/* Syllable generator
This object is responsible for parsing syllable rules and generating all combinations of syllables
*/
#ifndef LIB_SYLGENERATOR_CPP
#define LIB_SYLGENERATOR_CPP
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include "langgen/SylGenerator.h"

void SyllableGenerator::loadRulesGenerateWriteSyllables()
{
    std::vector<std::string> rules = loadRules(dirpath, rulesfile);
    std::vector<std::vector<std::set<std::vector<int>>>> parsedRules = parseGenerateRules(rules);
    std::vector<std::vector<int>> syllables = generateSyllables(parsedRules);
    std::vector<std::string> combinedSyllables = combineSyllables(syllables);
    writeSyllables(combinedSyllables, dirpath, outfile);
}

std::vector<std::string> SyllableGenerator::loadRules(std::string& dpath, std::string& rfile)
{
    std::string path = dpath + "/" + rfile;
    std::ifstream rf;

    try
    {
        rf.open(path);
    }
    catch (const std::ios_base::failure& fail)
    {
        std::cout << "Error: file " << path << " not found; " << fail.what() << std::endl;
    }

    std::string line;
    std::vector<std::string> rules;

    while (getline(rf, line))
    {
        if (line.empty())
        {
            continue;
        }
        rules.push_back(line);  
    }    
    return rules;
}

std::vector<std::vector<std::set<std::vector<int>>>> SyllableGenerator::parseGenerateRules(std::vector<std::string>& rules)
{

}

// in: ";+BILA,+VLSS,+STOP;+BILA,+STOP +LABD,+FRIC|+VOWL|+BILA,+VOIC,+STOP"
// out: {{{0}, {1}, {1, 16}, {1, 17}, {2, 16}, {2, 17}}, {{66}, {67}, {68}, ... {74}}, {{2}}}
// out: vector(set(onsets vectors), set(nuclei vectors), set(coda vectors))
std::vector<std::set<std::vector<int>>> SyllableGenerator::parseGenerateOneRule(std::string& rule)
{

}

// in: ";+BILA,+VLSS,+STOP;+BILA,+VOIC,+STOP +LABD,+VOIC,+FRIC|+VOWL|+BILA,+VOIC,+STOP"
// out: {";+BILA,+VLSS,+STOP;+BILA,+VOIC,+STOP +LABD,+VOIC,+FRIC", "+VOWL", "+BILA,+VOIC,+STOP"}
std::vector<std::string> SyllableGenerator::parseOneRule(std::string& rule)
{

}

// in: ";+BILA,+VLSS,+STOP;+BILA,+STOP +LABD,+FRIC"
// out: {"", "+BILA,+VLSS,+STOP", "+BILA,+VOIC,+STOP +LABD,+VOIC,+FRIC"}
std::vector<std::string> SyllableGenerator::parseSylPart(std::string& sylPart)
{

}

// in: "+BILA,+STOP +LABD,+FRIC"
// out: {{1, 16}, {1, 17}, {2, 16}, {2, 17}}
std::set<std::vector<int>> SyllableGenerator::parseOneSylPart(std::string& sylPart)
{

}

std::vector<std::vector<int>> SyllableGenerator::generateAllSyllables(std::vector<std::vector<std::set<std::vector<int>>>>& allOnsetsNucleiCodas)
{

}

// in: {{{0}, {1}, {1, 16}, {1, 17}, {2, 16}, {2, 17}}, {{66}, {67}, {68}, ... {74}}, {{2}}}
// out: {{0, 66, 2}, {1, 66, 2}, {1, 16, 66, 2}, ...}
std::vector<std::vector<int>> SyllableGenerator::generateSyllables(std::vector<std::set<std::vector<int>>>& onsetsNucleiCodas)
{

}

// in: {{0, 66, 2}, {1, 66, 2}, {1, 16, 66, 2}, ...}
// out: {"0|66|2", "1|66|2", "1|16|66|2", ...}
std::vector<std::string> SyllableGenerator::combineSyllables(std::vector<std::vector<int>>& syllables)
{

}

void SyllableGenerator::writeSyllables(std::vector<std::string>& syllables, std::string& dpath, std::string& outfile)
{

}


#endif