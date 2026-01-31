/* IPA Container
This object holds the IPA data for the syllable generation process
*/
#ifndef LANGGENLIB_IPACONTAINER_CPP
#define LANGGENLIB_IPACONTAINER_CPP
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "langgenLib/IPAContainer.h"

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
        else
        {
            item += ch;
        }
    }
    rangesets.push_back(item);
}

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
        row.push_back(tuple);
    }
}

IPA::IPA(std::string& DP, std::string& CC, std::string& VC, std::string& CK, std::string& VK)
{
    dirpath = DP;
    cipac = CC;
    vipac = VC;
    cipak = CK;
    vipak = VK;
}

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
        getRanges(rangesets, ranges);
        std::vector<std::vector<int>> expandedRanges;
        expandRanges(ranges, expandedRanges);
        wholekey.key.insert({catname, expandedRanges});
    }
    return wholekey;
}

#endif