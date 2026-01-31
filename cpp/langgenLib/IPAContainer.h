/* IPA Container
This object holds the IPA data for the syllable generation process
*/
#ifndef LANGGENLIB_IPACONTAINER_H
#define LANGGENLIB_IPACONTAINER_H
#include <string>
#include <vector>
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
    std::vector<int> getFeature(std::string&);
    std::vector<int> removeNotFeature(std::string&);
    std::string dirpath, cipac, vipac, cipak, vipak;
    IPAChart loadOneChart(std::string&);
    IPAKey loadOneKey(std::string&);
private:
    IPAChart cchart;
    IPAChart vchart;
    IPAKey ckey;
    IPAKey vkey;
};

#endif