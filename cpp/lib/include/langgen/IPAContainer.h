/* IPA Container
This object holds the IPA data for the syllable generation process
*/
#ifndef LIB_IPACONTAINER_H
#define LIB_IPACONTAINER_H
#include <string>
#include <vector>
#include <set>
#include <map>

struct IPAChart
{
    std::vector<std::vector<std::vector<int>>> chart;
};

struct IPAKey
{
    std::map<std::string, std::vector<std::vector<int>>> key;
};

// Helpers
void getCatnameRangesets(std::string&, std::string&, std::string&, std::vector<std::string>&);
void getRanges(std::vector<std::string>&, std::vector<std::vector<std::string>>&);
void expandRanges(std::vector<std::vector<std::string>>&, std::vector<std::vector<int>>&);
void getLineItems(std::string&, std::vector<std::string>&);
void getRow(std::vector<std::string>&, std::vector<std::vector<int>>&);

class IPA
{
public:
    IPA(std::string&, std::string&, std::string&, std::string&, std::string&);
    void loadIPAChartsKeys();
    std::vector<int> compileFeatures(std::vector<std::string>&, std::vector<std::string>&);
    void getFeatures(std::vector<std::string>&, std::set<int>&);
    void removeNotFeatures(std::vector<std::string>&, std::set<int>&);
    std::set<int> getFeature(std::string&);
    std::set<int> removeNotFeature(std::string&, std::set<int>&);
    IPAChart loadOneChart(std::string&);
    IPAKey loadOneKey(std::string&);
    std::string dirpath, cipac, vipac, cipak, vipak;
private:
    IPAChart cchart;
    IPAChart vchart;
    IPAKey ckey;
    IPAKey vkey;
};

#endif