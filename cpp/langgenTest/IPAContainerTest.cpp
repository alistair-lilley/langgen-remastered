/* Tests for IPAContainer
*/
#ifndef LANGGENTEST_IPACONTAINERTEST_CPP
#define LANGGENTEST_IPACONTAINERTEST_CPP
#include "IPAContainerTest.h"
#include <map>
#include <iostream>

IPA initializeIPA()
{
    std::string dirpath = "/home/ali/Projects/langgen/data/test";
    std::string cipak = "tCIPA.ipakey";
    std::string cipac = "tencoded.CIPA.ipachart";
    std::string vipac = "tencoded.VIPA.ipachart";
    std::string vipak = "tVIPA.ipakey";
    IPA ipa(dirpath, cipac, vipac, cipak, vipak);
    return ipa;
}

bool TestIPAloadOneChart(IPA& ipa)
{
    std::vector<std::vector<std::vector<int>>> truthchart = {
        {
            {1, 2},
            {0,0},
            {0,0},
            {3,4},
            {0,0},
            {5,6},
            {7,8},
            {9,10},
            {11,12},
            {0,0},
            {13,0},
        },
        {
            {14,15},
            {0,0},
            {0,0},
            {16,17},
            {0,0},
            {18,19},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
        }
    };
    try
    {
        IPAChart outchart = ipa.loadOneChart(ipa.cipac);
        return outchart.chart == truthchart;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

}

bool TestIPAloadOneKey(IPA& ipa)
{
    std::map<std::string, std::vector<std::vector<int>>> truthkey = {
        {"CONS", {
            {0, 1},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            {0, 1},
        }},
        {"VLSS", {
            {0, 1},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            {0},
        }},
        {"BILA", {
            {0, 1},
            {0},
            {0, 1}
        }}
    };
    try 
    {
        IPAKey outkey = ipa.loadOneKey(ipa.cipak);
        return outkey.key == truthkey;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool TestIPAgetFeature(IPA& ipa)
{
    std::set<int> truthset = {
        1, 3, 5, 7, 9, 11, 13, 14, 16, 18
    };
    try
    {
        ipa.loadIPAChartsKeys();
        std::string feature = "VLSS";
        std::set<int> phonemes = ipa.getFeature(feature);
        return phonemes == truthset;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

bool TestIPAremoveNotFeature(IPA& ipa)
{
    std::set<int> truthset = {
        3, 5, 7, 9, 11, 13, 16, 18
    };
    try
    {
        ipa.loadIPAChartsKeys();
        std::string feature = "VLSS";
        std::set<int> phonemes = ipa.getFeature(feature);
        std::string notFeature = "BILA";
        phonemes = ipa.removeNotFeature(notFeature, phonemes);
        return phonemes == truthset;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}


#endif