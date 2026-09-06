/* Syllable generator
This object is responsible for parsing syllable rules and generating all combinations of syllables
*/
#ifndef LIB_SYLGENERATOR_H
#define LIB_SYLGENERATOR_H
#include <string>
#include <vector>
#include "langgen/IPAContainer.h"

class SyllableGenerator
{
public:
    void loadRulesGenerateWriteSyllables();
    // Read file, return list of strings
    std::vector<std::string> loadRules(std::string&, std::string&);
    // Expand out all possible phonemes in their correct positions
    std::vector<std::vector<std::set<std::vector<int>>>> parseGenerateRules(std::vector<std::string>&); 
    std::vector<std::set<std::vector<int>>> parseGenerateOneRule(std::string&);
    std::vector<std::string> parseOneRule(std::string&);
    std::vector<std::string> parseSylPart(std::string&);
    std::set<std::vector<int>> parseOneSylPart(std::string&);
    // Create all individual syllables
    std::vector<std::vector<int>> generateAllSyllables(std::vector<std::vector<std::set<std::vector<int>>>>&);
    std::vector<std::vector<int>> generateSyllables(std::vector<std::set<std::vector<int>>>&);
    // Combine syllables into writeable form
    std::vector<std::string> combineSyllables(std::vector<std::vector<int>>&);
    // Write syllables to file
    void writeSyllables(std::vector<std::string>&, std::string&, std::string&);
private:
    std::string dirpath, rulesfile, outfile;
    IPA ipa;
};

#endif