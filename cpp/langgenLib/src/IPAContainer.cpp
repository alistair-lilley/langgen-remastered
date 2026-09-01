/* IPA Container
This object holds the IPA data for the syllable generation process
*/
#ifndef LANGGENLIB_IPACONTAINER_CPP
#define LANGGENLIB_IPACONTAINER_CPP
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "langgen/IPAContainer.h"

/*
Loading IPA charts and keys
Charts are in the format

```
1,2|0,0|0,0|3,4|0,0|5,6|7,8|9,10|11,12|0,0|13,0
14,15|0,0|0,0|16,17|0,0|18,19|0,0|0,0|0,0|0,0|0,0
```

The integers represent individual IPA characters that can't easily be represented in C++ cuz it 
hates unicode
We have to extract this into an indexing-friendly format, aka vector<vector<vector<int>>>
---------
Keys are in the format

```
CONS|0:4,6:8;0:11;0:2

VLSS|0:2;0:11;0:1
```

The 4-letter code at the beginning of each line represents the category name
The #:#,#:# pairs represent integer ranges in the form [start, end)
The ranges represent column, row, and pair indexing, e.g. referencing the chart above, VLSS would 
reference both rows, all columns, and only the first of each pair
We have to expand the pairs and map them to the category names, aka map<string, vector<vector<int>>>
*/

// Key extractors
// in: "CONS|0:4,6:8;0:11;0:2"
// out: catname = "CONS", rangesets = {"0:4,6:8". "0:11", "0:2"}
void getCatnameRangesets(std::string& line, std::string& catname, std::vector<std::string>& rangesets)
{
    std::string item;
    for (auto ch : line)
    {
        if (ch == '|')
        {
            catname = item;
            item = "";
        }
        else if (ch == ';')
        {
            rangesets.push_back(item);
            item = "";
        }
        else if (ch == '\n')
        {
            continue;
        }
        else
        {
            item += ch;
        }
    }
    rangesets.push_back(item);
}

// in: {"0:4,6:8", "0:11", "0:2"}
// out: {{"0:4", "6:8"}, {"0:11"}, {"0:2"}}
void getRanges(std::vector<std::string>& rangesets, std::vector<std::vector<std::string>>& ranges)
{
    int rangepos = 0;
    for (auto rangeset : rangesets)
    {
        std::string range;
        for (auto ch : rangeset)
        {
            if (ch == ',')
            {
                ranges.at(rangepos).push_back(range);
                range = "";
            }
            else
            {
                range += ch;
            }
        }
        ranges.at(rangepos).push_back(range);
        rangepos++;
    }
    rangepos = 0;
}

// in: {{"0:4", "6:8"}, {"0:11"}, {"0:2"}}
// out: 
void expandRanges(std::vector<std::vector<std::string>>& ranges, std::vector<std::vector<int>>& expandedRanges)
{
    int rangepos = 0;
    int start;
    int end;
    for (auto rangeset : ranges)
    {
        for (auto range : rangeset)
        {
            std::string rangenum;
            for (auto ch : range)
            {
                if (ch == ':')
                {
                    start = stoi(rangenum);
                    rangenum = "";
                }
                else
                {
                    rangenum += ch;
                }
            }
            end = stoi(rangenum);
            for (auto ii = start; ii < end; ii++)
            {
                expandedRanges.at(rangepos).push_back(ii);
            }
        }
        rangepos++;
    }
}


// Chart extractors
void getLineItems(std::string& line, std::vector<std::string>& lineitems)
{
    std::string lineitem;
    for(auto ch : line)
    {
        if (ch == '|')
        {
            lineitems.push_back(lineitem);
            lineitem = "";
        }
        else
        {
            lineitem += ch;
        }
    }
    lineitems.push_back(lineitem);
}

void getRow(std::vector<std::string>& lineitems, std::vector<std::vector<int>>& row)
{
    std::string pairitem;
    for (auto lineitem : lineitems)
    {
        std::vector<int> tuple;
        for (auto ch : lineitem)
        {
            if (ch == ',')
            {
                tuple.push_back(stoi(pairitem));
                pairitem = "";
            }
            else
            {
                pairitem += ch;
            }
        }
        tuple.push_back(stoi(pairitem));
        pairitem = "";
        row.push_back(tuple);
    }
}

// Object definition
IPA::IPA(std::string& DP, std::string& CC, std::string& VC, std::string& CK, std::string& VK)
{
    dirpath = DP;
    cipac = CC;
    vipac = VC;
    cipak = CK;
    vipak = VK;
}

// Loading one chart
IPAChart IPA::loadOneChart(std::string& chartname)
{
    std::string path = dirpath + "/" + chartname;
    std::ifstream chartfile;

    try
    {
        chartfile.open(path);
    }
    catch (const std::ios_base::failure& fail)
    {
        std::cout << "Error: file " << path << " not found; " << fail.what() << std::endl;
    }

    std::string line;
    IPAChart wholechart;

    while (getline(chartfile, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::vector<std::string> lineitems;
        getLineItems(line, lineitems);
        std::vector<std::vector<int>> row;
        getRow(lineitems, row);
        wholechart.chart.push_back(row);
    }    
    return wholechart;
}

IPAKey IPA::loadOneKey(std::string& keyname)
{
    std::string path = dirpath + "/" + keyname;
    std::ifstream keyfile;

    try
    {
        keyfile.open(path);
    }
    catch (const std::ios_base::failure& fail)
    {
        std::cout << "Error: file " << path << " not found; " << fail.what() << std::endl;
    }

    std::string line;
    IPAKey wholekey;

    while (getline(keyfile, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::string catname;
        std::vector<std::string> rangesets;
        getCatnameRangesets(line, catname, rangesets);
        std::vector<std::vector<std::string>> ranges;
        for(auto const& set : rangesets)
        {
            ranges.push_back(std::vector<std::string>());
        }
        getRanges(rangesets, ranges);
        std::vector<std::vector<int>> expandedRanges;
        for(auto const& range : ranges)
        {
            expandedRanges.push_back(std::vector<int>());
        }
        expandRanges(ranges, expandedRanges);
        wholekey.key.insert({catname, expandedRanges});
    }
    return wholekey;
}

#endif