/* Tests for IPAContainer
*/
#ifndef LANGGENTEST_IPACONTAINER_CPP
#define LANGGENTEST_IPACONTAINER_CPP
#include "langgenTest/IPAContainer.h"

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

bool TestIPAloadOneChart(IPA& ipa){
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
    IPAChart outchart = ipa.loadOneChart(ipa.cipac);
    return outchart.chart == truthchart;
}
}


#endif