/* IPA Container
This object holds the IPA data for the syllable generation process
*/
#ifndef LANGGENLIB_IPACONTAINER_H
#define LANGGENLIB_IPACONTAINER_H
#include <string>
#include <vector>
#include <map>

class IPA
{
public:
    IPA(std::string, std::string, std::string, std::string, std::string);
    void loadIPAChartsKeys();
    std::vector<int> getFeature(std::string);
    std::vector<int> removeNotFeature(std::string);
private:
    std::vector<std::vector<std::vector<int>>> cchart;
    std::vector<std::vector<std::vector<int>>> vchart;
    std::map<std::string, std::vector<int>> ckey;
    std::map<std::string, std::vector<int>> vkey;
    void loadOneChart(std::string);
    void loadOneKey(std::string);
};

#endif